#ifndef NAPTIEN_H
#define NAPTIEN_H

#include <string>
#include "Entity.h"

namespace NapTienConstants {
    const std::string METHOD_SCRATCH_CARD = "TheCao";
    const std::string METHOD_BANKING = "NganHang";
    const std::string METHOD_E_WALLET = "ViDienTu";

    const std::string STATUS_SUCCESS = "ThanhCong";
    const std::string STATUS_FAILED = "ThatBai";

    const int COL_WIDTH_ID = 12;
    const int COL_WIDTH_PHONE = 15;
    const int COL_WIDTH_DATE = 14;
    const int COL_WIDTH_AMOUNT = 16;
    const int COL_WIDTH_METHOD = 15;
    const int COL_WIDTH_STATUS = 14;
}

class NapTien : public Entity {
private:
    std::string soDienThoai;
    std::string ngayNap;
    double soTien;
    std::string hinhThucNap;
    std::string trangThai;

public:
    NapTien();
    NapTien(
        const std::string& maGD,
        const std::string& sdt,
        const std::string& ngay,
        double tien,
        const std::string& hinhThuc = NapTienConstants::METHOD_BANKING,
        const std::string& tThai = NapTienConstants::STATUS_SUCCESS
    );

    std::string getMaGiaoDich() const { return id; }
    std::string getSoDienThoai() const { return soDienThoai; }
    std::string getNgayNap() const { return ngayNap; }
    double getSoTien() const { return soTien; }
    std::string getHinhThucNap() const { return hinhThucNap; }
    std::string getTrangThai() const { return trangThai; }

    void setTrangThai(const std::string& tThai);

    void displayHeader() const override;
    void displayRow() const override;
    void displayDetail() const override;

    std::string toFileString() const override;
    bool fromFileString(const std::string& line) override;
};

#endif // NAPTIEN_H
