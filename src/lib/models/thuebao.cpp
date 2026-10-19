#include "thuebao.h"
#include "Date.h"
#include "Exceptions.h"
#include "fileio.h"
#include "Normalized.h"
#include "DisplayHelper.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace ThueBaoConstants;

ThueBao::ThueBao()
    : Entity(""),
      loaiThueBao(TYPE_PREPAID),
      maKhachHang(""),
      maGoiCuoc(""),
      ngayKichHoat(""),
      trangThai(STATUS_ACTIVE),
      soDuTaiKhoan(0.0) {}

ThueBao::ThueBao(
    const std::string& sdt,
    const std::string& loaiTB,
    const std::string& maKH,
    const std::string& maGC,
    const std::string& ngayKH,
    const std::string& tThai,
    double soDu
) : Entity(sdt),
    loaiThueBao(loaiTB),
    maKhachHang(maKH),
    maGoiCuoc(maGC),
    ngayKichHoat(ngayKH),
    trangThai(tThai),
    soDuTaiKhoan(soDu) {
    if (!Normalized::isValidPhoneNumber(id)) {
        throw InvalidPhoneNumberException(id);
    }
    if (maKhachHang.empty() || ngayKichHoat.empty()) {
        throw AppException("Loi: Thong tin bat buoc cua thue bao khong hop le!");
    }
    Date::parse(ngayKichHoat);
    if (loaiThueBao != TYPE_PREPAID && loaiThueBao != TYPE_POSTPAID) {
        throw AppException("Loi: Loai thue bao phai la 'TraTruoc' hoac 'TraSau'!");
    }
    if (trangThai != STATUS_ACTIVE && trangThai != STATUS_LOCKED_1WAY &&
        trangThai != STATUS_LOCKED_2WAY && trangThai != STATUS_CANCELLED) {
        throw AppException("Loi: Trang thai thue bao khong hop le!");
    }
    if (soDuTaiKhoan < 0.0) {
        throw AppException("Loi: So du tai khoan khong the am!");
    }
}

void ThueBao::setLoaiThueBao(const std::string& loai) {
    if (loai != TYPE_PREPAID && loai != TYPE_POSTPAID) {
        throw AppException("Loi: Loai thue bao phai la 'TraTruoc' hoac 'TraSau'!");
    }
    loaiThueBao = loai;
}

void ThueBao::setMaKhachHang(const std::string& maKH) {
    maKhachHang = maKH;
}

void ThueBao::setMaGoiCuoc(const std::string& maGC) {
    maGoiCuoc = maGC;
}

void ThueBao::setNgayKichHoat(const std::string& ngay) {
    ngayKichHoat = ngay;
}

void ThueBao::setTrangThai(const std::string& tThai) {
    trangThai = tThai;
}

void ThueBao::setSoDuTaiKhoan(double soDu) {
    soDuTaiKhoan = soDu;
}

void ThueBao::congTien(double tien) {
    if (tien <= 0) {
        throw AppException("Loi: So tien nap phai lon hon 0!");
    }
    soDuTaiKhoan += tien;
}

void ThueBao::truTien(double tien) {
    if (tien <= 0) {
        throw AppException("Loi: So tien tru phai lon hon 0!");
    }
    if (soDuTaiKhoan < tien && loaiThueBao == TYPE_PREPAID) {
        throw AppException("Loi: So du tai khoan khong du de thuc hien tru tien!");
    }
    soDuTaiKhoan -= tien;
}

void ThueBao::displayHeader() const {
    DisplayHelper::printHeader(
        {"So Dien Thoai", "Loai TB", "Ma KH", "Ma Goi", "Ngay KH", "Trang Thai", "So Du (VND)"},
        {COL_WIDTH_PHONE, COL_WIDTH_TYPE, COL_WIDTH_CUST, COL_WIDTH_PACKAGE, COL_WIDTH_DATE, COL_WIDTH_STATUS, COL_WIDTH_BALANCE},
        {false, false, false, false, false, false, true}
    );
}

void ThueBao::displayRow() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << soDuTaiKhoan;
    DisplayHelper::printRow(
        {id, loaiThueBao, maKhachHang, maGoiCuoc, ngayKichHoat, trangThai, oss.str()},
        {COL_WIDTH_PHONE, COL_WIDTH_TYPE, COL_WIDTH_CUST, COL_WIDTH_PACKAGE, COL_WIDTH_DATE, COL_WIDTH_STATUS, COL_WIDTH_BALANCE},
        {false, false, false, false, false, false, true}
    );
}

void ThueBao::displayDetail() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << soDuTaiKhoan << " VND";
    DisplayHelper::printCard({
        {"So dien thoai", id},
        {"Loai thue bao", loaiThueBao},
        {"Ma chu so huu", maKhachHang},
        {"Goi cuoc dang dung", maGoiCuoc.empty() ? "(Chua dang ky)" : maGoiCuoc},
        {"Ngay kich hoat", ngayKichHoat},
        {"Trang thai", trangThai},
        {"So du tai khoan", oss.str()}
    });
}

std::string ThueBao::toFileString() const {
    std::ostringstream oss;
    oss << id << "|"
        << loaiThueBao << "|"
        << maKhachHang << "|"
        << maGoiCuoc << "|"
        << ngayKichHoat << "|"
        << trangThai << "|"
        << std::fixed << std::setprecision(0) << soDuTaiKhoan;
    return oss.str();
}

bool ThueBao::fromFileString(const std::string& line) {
    std::vector<std::string> tokens = FileIO::split(line, '|');
    if (tokens.size() != 7) {
        return false;
    }

    try {
        //doc va kiem tra dinh dang thue bao,chong du thua
        size_t idxSoDu = 0;
        double soDu = std::stod(tokens[6], &idxSoDu);
        if (idxSoDu != tokens[6].length()) return false;
        ThueBao parsed(
            tokens[0],
            tokens[1],
            tokens[2],
            tokens[3],
            tokens[4],
            tokens[5],
            soDu
        );
        *this = parsed;
        return true;
    } catch (...) {
        return false;
    }
}
