
#ifndef KHACHHANG_H
#define KHACHHANG_H

#include <string>
#include "Entity.h"

namespace KhachHangConstants {
    const int COL_WIDTH_ID = 10;
    const int COL_WIDTH_NAME = 22;
    const int COL_WIDTH_DOC_TYPE = 12;
    const int COL_WIDTH_DOC_NUMBER = 18;
    const int COL_WIDTH_DATE = 13;
    const int COL_WIDTH_ISSUER = 25;
    const int COL_WIDTH_PHONE = 15;
    const int COL_WIDTH_ADDRESS = 20;
}

class KhachHang : public Entity {
private:
    std::string hoTen;
    std::string loaiGiayTo;
    std::string soGiayTo;
    std::string ngayCap;
    std::string noiCap;
    std::string soDienThoai;
    std::string diaChi;

public:
    KhachHang();
    
    KhachHang(
        const std::string& maKH,
        const std::string& hoTen,
        const std::string& loaiGiayTo,
        const std::string& soGiayTo,
        const std::string& ngayCap,
        const std::string& noiCap,
        const std::string& soDienThoai,
        const std::string& diaChi
    );

    std::string getMaKhachHang() const { return id; }
    std::string getHoTen() const { return hoTen; }
    std::string getLoaiGiayTo() const { return loaiGiayTo; }
    std::string getSoGiayTo() const { return soGiayTo; }
    std::string getNgayCap() const { return ngayCap; }
    std::string getNoiCap() const { return noiCap; }
    std::string getSoDienThoai() const { return soDienThoai; }
    std::string getDiaChi() const { return diaChi; }

    void setHoTen(const std::string& value);
    void setLoaiGiayTo(const std::string& value);
    void setSoGiayTo(const std::string& value);
    void setNgayCap(const std::string& value);
    void setNoiCap(const std::string& value);
    void setSoDienThoai(const std::string& value);
    void setDiaChi(const std::string& value);

    void displayHeader() const override;
    void displayRow() const override;
    void displayDetail() const override;

    std::string toFileString() const override;
    bool fromFileString(const std::string& line) override;
};

#endif // KHACHHANG_H
