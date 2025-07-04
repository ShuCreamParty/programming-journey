import tweepy
import os
import sys
import datetime
import smtplib
from email.mime.text import MIMEText
from email.header import Header
import jpholiday
import traceback
from dotenv import load_dotenv
import schedule
import time

load_dotenv()

API_KEY = os.environ.get("TWITTER_API_KEY")
API_SECRET_KEY = os.environ.get("TWITTER_API_SECRET_KEY")
ACCESS_TOKEN = os.environ.get("TWITTER_ACCESS_TOKEN")
ACCESS_TOKEN_SECRET = os.environ.get("TWITTER_ACCESS_TOKEN_SECRET")
BEARER_TOKEN = os.environ.get("TWITTER_BEARER_TOKEN")
GMAIL_ADDRESS = os.environ.get("GMAIL_ADDRESS")
GMAIL_APP_PASSWORD = os.environ.get("GMAIL_APP_PASSWORD")
NOTIFICATION_EMAIL = os.environ.get("NOTIFICATION_EMAIL")
REGULAR_TWEET_TEXT = "本日、アイスが３割引です!!!"

def send_email_notification(subject, body):
    if not all([GMAIL_ADDRESS, GMAIL_APP_PASSWORD, NOTIFICATION_EMAIL]):
        print(f"[{datetime.datetime.now()}] メール通知設定不十分。メール送信スキップ: {subject}", file=sys.stderr)
        return False
    try:
        smtp_host = 'smtp.gmail.com'
        smtp_port = 587
        msg = MIMEText(body, 'plain', 'utf-8')
        msg['Subject'] = Header(subject, 'utf-8')
        msg['From'] = GMAIL_ADDRESS
        msg['To'] = NOTIFICATION_EMAIL
        server = smtplib.SMTP(smtp_host, smtp_port)
        server.ehlo()
        server.starttls()
        server.ehlo()
        server.login(GMAIL_ADDRESS, GMAIL_APP_PASSWORD)
        server.send_message(msg)
        server.quit()
        print(f"[{datetime.datetime.now()}] メールを送信しました: {subject}")
        return True
    except Exception as e:
        print(f"[{datetime.datetime.now()}] メール送信中にエラー: {e}, 件名: {subject}", file=sys.stderr)
        traceback.print_exc(file=sys.stderr)
        return False

def post_tweet(text, is_error_tweet=False):
    tweet_type = 'エラー' if is_error_tweet else '通常'
    try:
        client = tweepy.Client(bearer_token=BEARER_TOKEN,
                               consumer_key=API_KEY,
                               consumer_secret=API_SECRET_KEY,
                               access_token=ACCESS_TOKEN,
                               access_token_secret=ACCESS_TOKEN_SECRET)
        response = client.create_tweet(text=text)
        print(f"[{datetime.datetime.now()}] {tweet_type}ツイート投稿成功: {text[:30]}...")
        return True, None
    except tweepy.errors.TweepyException as e:
        error_detail = f"Tweepyエラー: {e}\n"
        if hasattr(e, 'response') and e.response is not None:
            error_detail += f"API応答: {e.response.text}\n"
        if hasattr(e, 'api_codes'):
            error_detail += f"APIコード: {e.api_codes}\n"
        if hasattr(e, 'api_errors'):
            error_detail += f"APIエラー詳細: {e.api_errors}\n"
        print(f"[{datetime.datetime.now()}] {tweet_type}ツイート投稿Tweepyエラー:\n{error_detail}", file=sys.stderr)
        return False, error_detail
    except Exception as e:
        error_detail = f"予期せぬエラー: {e}"
        print(f"[{datetime.datetime.now()}] {tweet_type}ツイート投稿で予期せぬエラー:\n{error_detail}", file=sys.stderr)
        traceback.print_exc(file=sys.stderr)
        return False, error_detail

def check_post_condition():
    today = datetime.date.today()
    is_wednesday = today.weekday() == 2
    is_holiday = jpholiday.is_holiday(today)
    return is_wednesday and not is_holiday

def job():
    print(f"--- 定期処理開始 ({datetime.datetime.now()}) ---")
    start_time = datetime.datetime.now()
    script_status = "不明"
    final_message_details = ""
    error_occurred = False

    try:
        if not all([API_KEY, API_SECRET_KEY, ACCESS_TOKEN, ACCESS_TOKEN_SECRET]):
            message = "エラー: Twitter API に必要な認証情報が不足しています。"
            print(f"[{datetime.datetime.now()}] {message}", file=sys.stderr)
            send_email_notification(f"【緊急】Twitter Bot 起動/実行エラー ({start_time.strftime('%Y-%m-%d')})", message)
            return

        if check_post_condition():
            print(f"[{datetime.datetime.now()}] 投稿日です。ツイート処理を実行します。")
            success, error_info = post_tweet(REGULAR_TWEET_TEXT)
            if not success:
                error_occurred = True
                script_status = "ツイート失敗"
                final_message_details = f"エラー詳細:\n{error_info if error_info else '不明なエラー'}"
                print(f"[{datetime.datetime.now()}] !!! 通常ツイート投稿失敗。エラー通知処理開始 !!!", file=sys.stderr)
                email_subject = f"【要確認】Twitter Bot ツイートエラー ({start_time.strftime('%Y-%m-%d')})"
                email_body = f"実行日時: {start_time.strftime('%Y-%m-%d %H:%M:%S')}\n\n試行ツイート内容:\n{REGULAR_TWEET_TEXT}\n\n{final_message_details}"
                send_email_notification(email_subject, email_body)
                error_tweet_text = f"【Botエラー通知】{start_time.strftime('%H:%M')}頃の定期処理でエラーが発生しました。"
                post_tweet(error_tweet_text, is_error_tweet=True)
            else:
                script_status = "ツイート成功"
                final_message_details = f"ツイート内容:\n{REGULAR_TWEET_TEXT}"
                print(f"[{datetime.datetime.now()}] ツイート成功。")
        else:
            script_status = "ツイートスキップ"
            final_message_details = "本日は投稿日ではありません（水曜日ではない、または祝日です）。"
            print(f"[{datetime.datetime.now()}] {final_message_details}")

    except Exception as e:
        error_occurred = True
        script_status = "予期せぬエラー（job実行中）"
        tb_str = traceback.format_exc()
        final_message_details = f"エラータイプ: {type(e).__name__}\nエラー詳細: {e}\n\nトレースバック:\n{tb_str}"
        print(f"[{datetime.datetime.now()}] !!! job実行中に予期せぬエラー。緊急通知処理開始 !!!", file=sys.stderr)
        print(tb_str, file=sys.stderr)
        emergency_subject = f"【緊急】Twitter Bot 予期せぬエラー発生 ({start_time.strftime('%Y-%m-%d')})"
        emergency_body = f"定期ジョブ実行中に予期せぬエラーが発生しました。\n\n発生時刻: {start_time.strftime('%Y-%m-%d %H:%M:%S')}頃のジョブ\n\n{final_message_details}"
        send_email_notification(emergency_subject, emergency_body)

    finally:
        end_time = datetime.datetime.now()
        duration = end_time - start_time
        final_subject_prefix = "【完了】" if not error_occurred else ("【失敗】" if script_status != "ツイートスキップ" else "【情報】")
        if script_status == "ツイートスキップ" and not error_occurred:
            final_subject_prefix = "【情報】"

        final_subject = f"{final_subject_prefix}Twitter Bot 定期実行結果 ({start_time.strftime('%Y-%m-%d %H:%M')}) - {script_status}"
        final_body = f"定期実行開始: {start_time.strftime('%Y-%m-%d %H:%M:%S')}\n"
        final_body += f"実行終了: {end_time.strftime('%Y-%m-%d %H:%M:%S')}\n"
        final_body += f"処理時間: {duration}\n"
        final_body += f"最終ステータス: {script_status}\n\n"
        final_body += f"詳細情報:\n{final_message_details}\n"

        if all([GMAIL_ADDRESS, GMAIL_APP_PASSWORD, NOTIFICATION_EMAIL]):
            if not send_email_notification(final_subject, final_body):
                print(f"[{datetime.datetime.now()}] 最終結果メールの送信に失敗しました。件名: {final_subject}", file=sys.stderr)
        else:
            print(f"[{datetime.datetime.now()}] メール設定不十分のため、最終結果メールは送信できませんでした。", file=sys.stderr)

        print(f"--- 定期処理終了 ({datetime.datetime.now()}), 処理時間: {duration} ---")

if __name__ == "__main__":
    print(f"[{datetime.datetime.now()}] Twitter Bot スケジューラ起動。毎日11:55に処理を実行します。")
    schedule.every().day.at("11:55").do(job)
    try:
        while True:
            schedule.run_pending()
            time.sleep(1)
    except KeyboardInterrupt:
        print(f"[{datetime.datetime.now()}] Botを手動で停止しました。")
    except Exception as e:
        tb_str = traceback.format_exc()
        print(f"[{datetime.datetime.now()}] !!! スケジューラのメインループで予期せぬエラー発生 !!!", file=sys.stderr)
        print(tb_str, file=sys.stderr)
        emergency_subject = f"【緊急】Twitter Bot スケジューラ自体がエラー停止 ({datetime.datetime.now().strftime('%Y-%m-%d')})"
        emergency_body = f"Twitter Botのスケジューラが予期せぬエラーで停止した可能性があります。\n\n時刻: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\nエラー:\n{tb_str}"
        send_email_notification(emergency_subject, emergency_body)
