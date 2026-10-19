#ifndef HOADON_H
#define HOADON_H

#include <string>
#include "Entity.h"

namespace HoaDonConstants {
    const std::string STATUS_PAID = "DaThanhToan";
    const std::string STATUS_UNPAID = "ChuaThanhToan";

    const int COL_WIDTH_ID = 10;
    const int COL_WIDTH_PHONE = 15;
    const int COL_WIDTH_CYCLE = 12;
    const int COL_WIDTH_CALL = 14;
    const int COL_WIDTH_DATA = 14;
    const int COL_WIDTH_TOTAL = 16;
    const int COL_WIDTH_STATUS = 15;
}

class HoaDon : public Entity {
private:
    std::string soDienThoai;
    std::string kyCuoc;//ky cuoc mm/yyyy
    double tienGoi;
    double tienData;
    double tongTien;
    std::string trangThai;

public:
    HoaDon();
    HoaDon(
        const std::string& maHD,
        const std::string& sdt,
        const std::string& ky,
        double tGoi,
        double tData,
        double tong,
        const std::string& tThai = HoaDonConstants::STATUS_PAID
    );

    std::string getMaHoaDon() const { return id; }
    std::string getSoDienThoai() const { return soDienThoai; }
    std::string getKyCuoc() const { return kyCuoc; }
    double getTienGoi() const { return tienGoi; }
    double getTienData() const { return tienData; }
    double getTongTien() const { return tongTien; }
    std::string getTrangThai() const { return trangThai; }

    void setTrangThai(const std::string& tThai);
    void thanhToan();

    void displayHeader() const override;
    void displayRow() const override;
    void displayDetail() const override;

    std::string toFileString() const override;
    bool fromFileString(const std::string& line) override;
};

#endif // HOADON_H
