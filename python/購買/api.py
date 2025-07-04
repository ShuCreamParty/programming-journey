from flask import Flask, request, jsonify
import schedule
import time
import datetime
import threading # スケジューラを別スレッドで動かすため
import os
from dotenv import load_dotenv
# ... (あなたの purchase.py から必要な関数や設定を import またはここに記述) ...
# 例: from purchase_logic import job, regular_wednesday_job, run_once_specific_date_job, ...

load_dotenv()
app = Flask(__name__)

# --- 認証用の簡単なAPIキー (実際にはもっと安全な方法を検討) ---
# 環境変数や設定ファイルから読み込むのが良い
API_ACCESS_KEY = os.environ.get("MY_BOT_API_KEY", "default_secret_key")


# --- スケジューラのロジック (purchase.py から持ってくるか、別モジュール化) ---
# 例:
# def regular_wednesday_job(): ...
# def run_once_specific_date_job(target_date_str, message, job_id_tag): ...
# def post_tweet(text, is_error_tweet=False): ...
# などをここに定義するか、別ファイルから import する。
# ここでは、簡単化のため、スケジュールの操作部分のみをAPI化するイメージで進めます。
# 実際のツイート処理などは、スケジュールされたジョブ関数内で実行されます。

# スケジュールされたジョブを管理するリスト (実際にはもっと堅牢な管理が必要)
# schedule.jobs を直接参照・操作する方が良い場合もある

# 簡単な認証デコレータ
def require_api_key(f):
    def decorated_function(*args, **kwargs):
        if request.headers.get('X-Api-Key') and request.headers.get('X-Api-Key') == API_ACCESS_KEY:
            return f(*args, **kwargs)
        else:
            return jsonify({"error": "Unauthorized"}), 401
    decorated_function.__name__ = f.__name__ # デコレータ使用時のエラー回避
    return decorated_function

@app.route('/add_schedule', methods=['POST'])
@require_api_key
def add_schedule_route():
    data = request.json
    try:
        date_str = data['date'] # YYYY-MM-DD
        time_str = data['time'] # HH:MM
        message = data['message']
        job_id = data.get('id', f"custom_{date_str.replace('-', '')}_{time_str.replace(':', '')}") # 簡単なID生成

        # schedule.every().day.at(time_str).do(
        #     run_once_specific_date_job,
        #     target_date_str=date_str,
        #     message=message,
        #     job_id_tag=job_id
        # ).tag("custom_schedule", job_id)
        # print(f"API: カスタムスケジュール追加: {job_id} - {date_str} {time_str} \"{message[:20]}...\"")

        # ここで実際に schedule ライブラリを操作してジョブを追加
        # 例: (実際のジョブ関数は別途定義されている想定)
        # schedule.every().day.at(time_str).do(custom_tweet_job, message=message, target_date=date_str).tag(job_id, "custom")

        return jsonify({"message": "Schedule added successfully", "job_id": job_id}), 200
    except KeyError as e:
        return jsonify({"error": f"Missing data: {e}"}), 400
    except Exception as e:
        return jsonify({"error": f"Failed to add schedule: {str(e)}"}), 500

@app.route('/remove_schedule', methods=['POST'])
@require_api_key
def remove_schedule_route():
    data = request.json
    try:
        identifier = data['identifier'] # ID or date for regular cancellation

        # schedule.clear(identifier) # タグで指定してジョブを削除
        # print(f"API: スケジュール削除試行: {identifier}")
        
        # もし定期投稿のキャンセルなら、設定ファイルやDBを更新するロジック
        # if data.get("type") == "cancel_regular":
        #    add_to_cancel_list(identifier) # identifier は日付 YYYY-MM-DD

        return jsonify({"message": f"Schedule related to '{identifier}' removal attempted."}), 200
    except KeyError:
        return jsonify({"error": "Missing identifier"}), 400
    except Exception as e:
        return jsonify({"error": f"Failed to remove schedule: {str(e)}"}), 500

@app.route('/booklist', methods=['GET'])
@require_api_key
def booklist_route():
    # current_jobs = []
    # for job_item in schedule.jobs:
    #     current_jobs.append({
    #         "next_run": str(job_item.next_run),
    #         "tags": list(job_item.tags),
    #         "at_time": str(job_item.at_time) if hasattr(job_item, 'at_time') and job_item.at_time else None,
    #         # "message": job_item.job_func.args などから取得 (工夫が必要)
    #     })
    # return jsonify({"schedules": current_jobs}), 200
    return jsonify({"message": "Booklist endpoint (implement me)"}), 200


# --- スケジューラを別スレッドで実行する関数 ---
def run_scheduler():
    print("Scheduler thread started.")
    # ここに purchase.py の if __name__ == "__main__": の中身（schedule設定とループ）を移植
    # schedule.every().wednesday.at("11:55").do(regular_wednesday_job).tag("regular_wednesday")
    # ... 他の初期スケジュール設定 ...
    
    # 起動時に一度booklistを表示するようなものは、API経由にするか、起動ログに留める
    # show_booklist() # APIサーバー起動時のログとして出すならここ

    while True:
        schedule.run_pending()
        time.sleep(1)

if __name__ == '__main__':
    # スケジューラを別スレッドで開始
    scheduler_thread = threading.Thread(target=run_scheduler, daemon=True)
    scheduler_thread.start()

    # Flaskアプリを実行 (0.0.0.0 で外部からのアクセスを許可)
    # ポート番号は空いているものを選ぶ (例: 5000)
    # 実際にはGunicornなどのWSGIサーバーを使うのが本番環境では推奨される
    print("Flask API server starting on port 5000...")
    app.run(host='0.0.0.0', port=5000, debug=False) # debug=True は開発時のみ