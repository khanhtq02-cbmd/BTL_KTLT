#ifndef THUEBAO_H
#define THUEBAO_H

#include <string>
#include "Entity.h"

namespace ThueBaoConstants {
    const std::string TYPE_PREPAID = "TraTruoc";
    const std::string TYPE_POSTPAID = "TraSau";

    const std::string STATUS_ACTIVE = "HoatDong";
    const std::string STATUS_LOCKED_1WAY = "Khoa1Chieu";
    const std::string STATUS_LOCKED_2WAY = "Khoa2Chieu";
    const std::string STATUS_CANCELLED = "Huy";

    const int COL_WIDTH_PHONE = 15;
    const int COL_WIDTH_TYPE = 12;
    const int COL_WIDTH_CUST = 10;
    const int COL_WIDTH_PACKAGE = 10;
    const int COL_WIDTH_DATE = 13;
    const int COL_WIDTH_STATUS = 14;
    const int COL_WIDTH_BALANCE = 16;
}

class ThueBao : public Entity {
private:
    std::string loaiThueBao;
    std::string maKhachHang;
    std::string maGoiCuoc;
    std::string ngayKichHoat;
    std::string trangThai;
    double soDuTaiKhoan;

public:
    ThueBao();
    ThueBao(
        const std::string& soDienThoai,
        const std::string& loaiTB,
        const std::string& maKH,
        const std::string& maGC,
        const std::string& ngayKH,
        const std::string& tThai = ThueBaoConstants::STATUS_ACTIVE,
        double soDu = 0.0
    );

    std::string getSoDienThoai() const { return id; }
    std::string getLoaiThueBao() const { return loaiThueBao; }
    std::string getMaKhachHang() const { return maKhachHang; }
    std::string getMaGoiCuoc() const { return maGoiCuoc; }
    std::string getNgayKichHoat() const { return ngayKichHoat; }
    std::string getTrangThai() const { return trangThai; }
    double getSoDuTaiKhoan() const { return soDuTaiKhoan; }

    void setLoaiThueBao(const std::string& loai);
    void setMaKhachHang(const std::string& maKH);
    void setMaGoiCuoc(const std::string& maGC);
    void setNgayKichHoat(const std::string& ngay);
    void setTrangThai(const std::string& tThai);
    void setSoDuTaiKhoan(double soDu);
    void congTien(double tien);
    void truTien(double tien);

    void displayHeader() const override;
    void displayRow() const override;
    void displayDetail() const override;

    std::string toFileString() const override;
    bool fromFileString(const std::string& line) override;
};

#endif // THUEBAO_H
