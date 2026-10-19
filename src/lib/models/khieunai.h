#ifndef KHIEUNAI_H
#define KHIEUNAI_H

#include <string>
#include "Entity.h"

namespace KhieuNaiConstants {
    const std::string TYPE_BILLING = "CuocPhatSinh";
    const std::string TYPE_NETWORK = "ChatLuongMang";
    const std::string TYPE_CARD = "TheCao";
    const std::string TYPE_SERVICE = "DichVuGoi";

    const std::string STATUS_RECEIVED = "TiepNhan";
    const std::string STATUS_PROCESSING = "DangXuLy";
    const std::string STATUS_RESOLVED = "DaGiaiQuyet";
    const std::string STATUS_REJECTED = "TuChoi";

    const int COL_WIDTH_ID = 12;
    const int COL_WIDTH_PHONE = 15;
    const int COL_WIDTH_TYPE = 16;
    const int COL_WIDTH_DATE = 14;
    const int COL_WIDTH_STATUS = 14;
    const int COL_WIDTH_CONTENT = 30;
}

class KhieuNai : public Entity {
private:
    std::string soDienThoai;
    std::string loaiKhieuNai;
    std::string ngayTiepNhan;
    std::string noiDung;
    std::string trangThai;

public:
    KhieuNai();
    KhieuNai(
        const std::string& maKN,
        const std::string& sdt,
        const std::string& loai,
        const std::string& ngay,
        const std::string& content,
        const std::string& status = KhieuNaiConstants::STATUS_RECEIVED
    );

    std::string getMaKhieuNai() const { return id; }
    std::string getSoDienThoai() const { return soDienThoai; }
    std::string getLoaiKhieuNai() const { return loaiKhieuNai; }
    std::string getNgayTiepNhan() const { return ngayTiepNhan; }
    std::string getNoiDung() const { return noiDung; }
    std::string getTrangThai() const { return trangThai; }

    void setTrangThai(const std::string& status);

    void displayHeader() const override;
    void displayRow() const override;
    void displayDetail() const override;

    std::string toFileString() const override;
    bool fromFileString(const std::string& line) override;
};

#endif // KHIEUNAI_H
