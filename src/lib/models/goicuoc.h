#ifndef GOICUOC_H
#define GOICUOC_H

#include <string>
#include "Entity.h"

namespace GoiCuocConstants {
    const int COL_WIDTH_ID = 10;
    const int COL_WIDTH_NAME = 20;
    const int COL_WIDTH_PRICE = 14;
    const int COL_WIDTH_DATA = 12;
    const int COL_WIDTH_VOICE = 14;
    const int COL_WIDTH_CYCLE = 12;
}

class GoiCuoc : public Entity {
private:
    std::string tenGoi;
    double giaCuoc;
    int dungLuongData;//dung luong gb
    int soPhutGoi;//so phut thoai
    int chuKyNgay;//chu ky ngay

public:
    GoiCuoc();
    GoiCuoc(
        const std::string& maGoi,
        const std::string& tenGoi,
        double giaCuoc,
        int dungLuongData,
        int soPhutGoi,
        int chuKyNgay = 30
    );

    std::string getMaGoi() const { return id; }
    std::string getTenGoi() const { return tenGoi; }
    double getGiaCuoc() const { return giaCuoc; }
    int getDungLuongData() const { return dungLuongData; }
    int getSoPhutGoi() const { return soPhutGoi; }
    int getChuKyNgay() const { return chuKyNgay; }

    void setTenGoi(const std::string& ten);
    void setGiaCuoc(double gia);
    void setDungLuongData(int data);
    void setSoPhutGoi(int phut);
    void setChuKyNgay(int chuky);

    void displayHeader() const override;
    void displayRow() const override;
    void displayDetail() const override;

    std::string toFileString() const override;
    bool fromFileString(const std::string& line) override;
};

#endif // GOICUOC_H
