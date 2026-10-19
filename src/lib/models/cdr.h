#ifndef CDR_H
#define CDR_H

#include <string>
#include "Entity.h"

namespace CDRConstants {
    const std::string TYPE_VOICE = "Thoai";
    const std::string TYPE_SMS = "SMS";
    const std::string TYPE_DATA = "Data";

    const int COL_WIDTH_ID = 12;
    const int COL_WIDTH_CALLER = 14;
    const int COL_WIDTH_RECEIVER = 14;
    const int COL_WIDTH_TYPE = 10;
    const int COL_WIDTH_TIME = 22;
    const int COL_WIDTH_DURATION = 14;
    const int COL_WIDTH_COST = 14;
}

class CDR : public Entity {
private:
    std::string soGoi;
    std::string soNhan;
    std::string loaiDichVu;
    std::string thoiGianBatDau;
    int thoiLuong; // giay (hoac MB voi Data)
    double cuocPhatSinh; // VND

public:
    CDR();
    CDR(
        const std::string& maCDR,
        const std::string& caller,
        const std::string& receiver,
        const std::string& type,
        const std::string& startTime,
        int duration,
        double cost
    );

    std::string getMaCDR() const { return id; }
    std::string getSoGoi() const { return soGoi; }
    std::string getSoNhan() const { return soNhan; }
    std::string getLoaiDichVu() const { return loaiDichVu; }
    std::string getThoiGianBatDau() const { return thoiGianBatDau; }
    int getThoiLuong() const { return thoiLuong; }
    double getCuocPhatSinh() const { return cuocPhatSinh; }

    void displayHeader() const override;
    void displayRow() const override;
    void displayDetail() const override;

    std::string toFileString() const override;
    bool fromFileString(const std::string& line) override;
};

#endif // CDR_H
