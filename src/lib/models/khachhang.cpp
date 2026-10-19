#include "khachhang.h"
#include "Date.h"
#include "Exceptions.h"
#include "fileio.h"
#include "Normalized.h"
#include "DisplayHelper.h"
#include <iostream>
#include <sstream>

using namespace KhachHangConstants;

KhachHang::KhachHang()
    : Entity(""),
      hoTen(""),
      loaiGiayTo("CCCD"),
      soGiayTo(""),
      ngayCap(""),
      noiCap(""),
      soDienThoai(""),
      diaChi("") {}

KhachHang::KhachHang(
    const std::string& maKH,
    const std::string& ten,
    const std::string& loaiGT,
    const std::string& soGT,
    const std::string& nCap,
    const std::string& noiC,
    const std::string& sdt,
    const std::string& dc
) : Entity(maKH),
    hoTen(ten),
    loaiGiayTo(loaiGT),
    soGiayTo(soGT),
    ngayCap(nCap),
    noiCap(noiC),
    soDienThoai(sdt),
    diaChi(dc) {
    if (id.empty() || hoTen.empty() || loaiGiayTo.empty() || soGiayTo.empty() ||
        ngayCap.empty() || noiCap.empty() || soDienThoai.empty() || diaChi.empty()) {
        throw AppException("Loi: Thong tin bat buoc cua khach hang khong hop le!");
    }
    Date::parse(ngayCap);
    if (!Normalized::isValidPhoneNumber(soDienThoai)) {
        throw InvalidPhoneNumberException(soDienThoai);
    }
}

void KhachHang::setHoTen(const std::string& value) {
    hoTen = value;
}

void KhachHang::setLoaiGiayTo(const std::string& value) {
    loaiGiayTo = value;
}

void KhachHang::setSoGiayTo(const std::string& value) {
    soGiayTo = value;
}

void KhachHang::setNgayCap(const std::string& value) {
    ngayCap = value;
}

void KhachHang::setNoiCap(const std::string& value) {
    noiCap = value;
}

void KhachHang::setSoDienThoai(const std::string& value) {
    if (!value.empty() && !Normalized::isValidPhoneNumber(value)) {
        throw InvalidPhoneNumberException(value);
    }
    soDienThoai = value;
}

void KhachHang::setDiaChi(const std::string& value) {
    diaChi = value;
}

void KhachHang::displayHeader() const {
    DisplayHelper::printHeader(
        {"Ma KH", "Ho Va Ten", "Loai GT", "So Giay To", "Ngay Cap", "Noi Cap", "So Dien Thoai", "Dia Chi"},
        {COL_WIDTH_ID, COL_WIDTH_NAME, COL_WIDTH_DOC_TYPE, COL_WIDTH_DOC_NUMBER, COL_WIDTH_DATE, COL_WIDTH_ISSUER, COL_WIDTH_PHONE, COL_WIDTH_ADDRESS},
        {false, false, false, false, false, false, false, false}
    );
}

void KhachHang::displayRow() const {
    DisplayHelper::printRow(
        {id, hoTen, loaiGiayTo, soGiayTo, ngayCap, noiCap, soDienThoai, diaChi},
        {COL_WIDTH_ID, COL_WIDTH_NAME, COL_WIDTH_DOC_TYPE, COL_WIDTH_DOC_NUMBER, COL_WIDTH_DATE, COL_WIDTH_ISSUER, COL_WIDTH_PHONE, COL_WIDTH_ADDRESS},
        {false, false, false, false, false, false, false, false}
    );
}

void KhachHang::displayDetail() const {
    DisplayHelper::printCard({
        {"Ma khach hang", id},
        {"Ho va ten", hoTen},
        {"Loai giay to", loaiGiayTo},
        {"So giay to", soGiayTo},
        {"Ngay cap", ngayCap},
        {"Noi cap", noiCap},
        {"So dien thoai", soDienThoai},
        {"Dia chi", diaChi}
    });
}

std::string KhachHang::toFileString() const {
    std::ostringstream oss;
    oss << id << "|"
        << hoTen << "|"
        << loaiGiayTo << "|"
        << soGiayTo << "|"
        << ngayCap << "|"
        << noiCap << "|"
        << soDienThoai << "|"
        << diaChi;
    return oss.str();
}

bool KhachHang::fromFileString(const std::string& line) {
    std::vector<std::string> tokens = FileIO::split(line, '|');
    const size_t EXPECTED_FIELD_COUNT = 8;
    if (tokens.size() != EXPECTED_FIELD_COUNT) {
        return false;
    }

    try {
        //doc va kiem tra thong tin khach hang,chan du thua
        KhachHang parsed(
            tokens[0],
            tokens[1],
            tokens[2],
            tokens[3],
            tokens[4],
            tokens[5],
            tokens[6],
            tokens[7]
        );
        *this = parsed;
        return true;
    } catch (...) {
        return false;
    }
}
