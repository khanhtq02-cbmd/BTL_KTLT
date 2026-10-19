#include "hoadon.h"
#include "Exceptions.h"
#include "fileio.h"
#include "Normalized.h"
#include "DisplayHelper.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace HoaDonConstants;

HoaDon::HoaDon()
    : Entity(""),
      soDienThoai(""),
      kyCuoc(""),
      tienGoi(0.0),
      tienData(0.0),
      tongTien(0.0),
      trangThai(STATUS_PAID) {}

HoaDon::HoaDon(
    const std::string& maHD,
    const std::string& sdt,
    const std::string& ky,
    double tGoi,
    double tData,
    double tong,
    const std::string& tThai
) : Entity(maHD),
    soDienThoai(sdt),
    kyCuoc(ky),
    tienGoi(tGoi),
    tienData(tData),
    tongTien(tong),
    trangThai(tThai) {
    if (id.empty() || soDienThoai.empty() || kyCuoc.empty()) {
        throw AppException("Loi: Thong tin bat buoc cua hoa don khong hop le!");
    }
    if (!Normalized::isValidPhoneNumber(sdt)) {
        throw InvalidPhoneNumberException(sdt);
    }
    if (tienGoi < 0.0 || tienData < 0.0 || tongTien < 0.0) {
        throw AppException("Loi: So tien tren hoa don khong the am!");
    }
    if (trangThai != STATUS_PAID && trangThai != STATUS_UNPAID) {
        throw AppException("Loi: Trang thai hoa don khong hop le!");
    }
}

void HoaDon::setTrangThai(const std::string& tThai) {
    trangThai = tThai;
}

void HoaDon::thanhToan() {
    trangThai = STATUS_PAID;
}

void HoaDon::displayHeader() const {
    DisplayHelper::printHeader(
        {"Ma HD", "So Dien Thoai", "Ky Cuoc", "Tien Goi (VND)", "Tien Data (VND)", "Tong Cong (VND)", "Trang Thai"},
        {COL_WIDTH_ID, COL_WIDTH_PHONE, COL_WIDTH_CYCLE, COL_WIDTH_CALL, COL_WIDTH_DATA, COL_WIDTH_TOTAL, COL_WIDTH_STATUS},
        {false, false, false, true, true, true, false}
    );
}

void HoaDon::displayRow() const {
    std::ostringstream ossGoi, ossData, ossTong;
    ossGoi << std::fixed << std::setprecision(0) << tienGoi;
    ossData << std::fixed << std::setprecision(0) << tienData;
    ossTong << std::fixed << std::setprecision(0) << tongTien;

    DisplayHelper::printRow(
        {id, soDienThoai, kyCuoc, ossGoi.str(), ossData.str(), ossTong.str(), trangThai},
        {COL_WIDTH_ID, COL_WIDTH_PHONE, COL_WIDTH_CYCLE, COL_WIDTH_CALL, COL_WIDTH_DATA, COL_WIDTH_TOTAL, COL_WIDTH_STATUS},
        {false, false, false, true, true, true, false}
    );
}

void HoaDon::displayDetail() const {
    std::ostringstream ossGoi, ossData, ossTong;
    ossGoi << std::fixed << std::setprecision(0) << tienGoi << " VND";
    ossData << std::fixed << std::setprecision(0) << tienData << " VND";
    ossTong << std::fixed << std::setprecision(0) << tongTien << " VND";

    DisplayHelper::printCard({
        {"Ma hoa don", id},
        {"So dien thoai", soDienThoai},
        {"Ky cuoc", kyCuoc},
        {"Tien cuoc thoai", ossGoi.str()},
        {"Tien cuoc data", ossData.str()},
        {"Tong tien thanh toan", ossTong.str()},
        {"Trang thai", trangThai}
    });
}

std::string HoaDon::toFileString() const {
    std::ostringstream oss;
    oss << id << "|"
        << soDienThoai << "|"
        << kyCuoc << "|"
        << std::fixed << std::setprecision(0) << tienGoi << "|"
        << std::fixed << std::setprecision(0) << tienData << "|"
        << std::fixed << std::setprecision(0) << tongTien << "|"
        << trangThai;
    return oss.str();
}

bool HoaDon::fromFileString(const std::string& line) {
    std::vector<std::string> tokens = FileIO::split(line, '|');
    if (tokens.size() != 7) {
        return false;
    }

    try {
        //doc va kiem tra gia tri hoa don,chong du thua
        size_t i1 = 0, i2 = 0, i3 = 0;
        double tGoi = std::stod(tokens[3], &i1);
        double tData = std::stod(tokens[4], &i2);
        double tong = std::stod(tokens[5], &i3);
        if (i1 != tokens[3].length() || i2 != tokens[4].length() || i3 != tokens[5].length()) {
            return false;
        }
        HoaDon parsed(
            tokens[0],
            tokens[1],
            tokens[2],
            tGoi,
            tData,
            tong,
            tokens[6]
        );
        *this = parsed;
        return true;
    } catch (...) {
        return false;
    }
}
