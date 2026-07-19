#include <iostream>
#include <datetime.hpp>

using namespace std;
using namespace dt;

int main() {
    try {
        timedelta td1(2, 3600, 500000);
        timedelta td2(1, 7200, 600000);
        timedelta td_sum = td1 + td2;
        timedelta td_diff = td1 - td2;

        cout << "Khoảng thời gian ngày: " << td1.days << endl;
        cout << "Khoảng thời gian giây: " << td1.seconds << endl;
        cout << "Khoảng thời gian micrô giây: " << td1.microseconds << endl;
        cout << "Tổng số giây: " << td1.total_seconds() << endl;
        cout << "Cộng khoảng thời gian giây: " << td_sum.total_seconds() << endl;
        cout << "Trừ khoảng thời gian giây: " << td_diff.total_seconds() << endl;

        date d1(2026, 7, 19);
        date d_today = date::today();

        cout << "Năm của ngày: " << d1.year << endl;
        cout << "Tháng của ngày: " << d1.month << endl;
        cout << "Ngày của tháng: " << d1.day << endl;
        cout << "Ngày hôm nay định dạng ISO: " << d_today.isoformat() << endl;
        cout << "Định dạng ngày tùy chỉnh: " << d1.strftime("%d/%m/%Y") << endl;
        cout << "Ngày trong tuần từ số 0: " << d1.weekday() << endl;

        dt::time t1(14, 30, 15, 123456);

        cout << "Giờ: " << t1.hour << endl;
        cout << "Phút: " << t1.minute << endl;
        cout << "Giây: " << t1.second << endl;
        cout << "Micrô giây: " << t1.microsecond << endl;
        cout << "Định dạng giờ ISO: " << t1.isoformat() << endl;
        cout << "Định dạng giờ tùy chỉnh: " << t1.strftime("%H-%M-%S") << endl;

        datetime dt1(2026, 7, 19, 10, 20, 30, 50000);
        datetime dt_now = datetime::now();

        cout << "Năm của ngày giờ: " << dt1.year << endl;
        cout << "Tháng của ngày giờ: " << dt1.month << endl;
        cout << "Ngày của ngày giờ: " << dt1.day << endl;
        cout << "Giờ của ngày giờ: " << dt1.hour << endl;
        cout << "Phút của ngày giờ: " << dt1.minute << endl;
        cout << "Giây của ngày giờ: " << dt1.second << endl;
        cout << "Micrô giây của ngày giờ: " << dt1.microsecond << endl;
        cout << "Thời gian hiện tại định dạng ISO: " << dt_now.isoformat() << endl;
        cout << "Định dạng ngày giờ tùy chỉnh: " << dt1.strftime("%Y/%m/%d %H:%M:%S") << endl;

        date extracted_date = dt1.date_part();
        dt::time extracted_time = dt1.time_part();
        cout << "Tách phần ngày: " << extracted_date.isoformat() << endl;
        cout << "Tách phần giờ: " << extracted_time.isoformat() << endl;

        datetime parsed_dt = datetime::strptime("2026-05-12 18:45:00", "%Y-%m-%d %H:%M:%S");
        cout << "Chuyển chuỗi thành ngày giờ: " << parsed_dt.isoformat() << endl;

        auto tp = dt1.to_time_point();
        datetime from_tp = datetime::from_time_point(tp);
        cout << "Chuyển từ điểm thời gian: " << from_tp.isoformat() << endl;

        datetime dt_plus = dt1 + td1;
        datetime dt_minus = dt1 - td1;
        timedelta dt_diff_res = dt_plus - dt1;

        cout << "Cộng ngày giờ với khoảng thời gian: " << dt_plus.isoformat() << endl;
        cout << "Trừ ngày giờ với khoảng thời gian: " << dt_minus.isoformat() << endl;
        cout << "Hiệu hai ngày giờ ra số ngày: " << dt_diff_res.days << endl;

    } catch (const exception& e) {
        cout << "Lỗi hệ thống: " << e.what() << endl;
        return 1;
    }

    return 0;
}