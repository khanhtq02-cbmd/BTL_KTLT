/**
 * @file NapTienMenu.cpp
 * Thành viên phụ trách: Phạm Đức Chính (B24DCVT047)
 * Học phần: Kỹ thuật lập trình (KTLT) - PTIT
 */

#include "NapTienMenu.h"
#include "InputHelper.h"
#include "DisplayHelper.h"
#include "Normalized.h"
#include <iostream>

using namespace NapTienMenuChoices;

// Lập phiếu nạp tiền và cập nhật số dư
void NapTienMenu::lapPhieuNapTien() {
    std::cout << "\n>>> LAP PHIEU NAP TIEN VAO TAI KHOAN <<<\n";
    std::string maGD = InputHelper::getString("Nhap ma giao dich (VD: GD0010): ");
    if (std::cin.eof() || maGD.empty()) return;
    if (napTienStore.findById(maGD) != nullptr) {
        std::cout << "[CANH BAO] Ma giao dich da ton tai trong he thong!\n";
        return;
    }

    std::string sdt = InputHelper::getPhoneNumber("Nhap so dien thoai can nap: ", false);
    if (std::cin.eof() || sdt.empty()) return;
    ThueBao* tb = thueBaoStore.findById(sdt);
    if (tb == nullptr) {
        std::cout << "[LOI] So thue bao '" << sdt << "' chua duoc dang ky tren he thong!\n";
        return;
    }

    std::cout << "So du hien tai cua thue bao " << sdt << ": "
              << DisplayHelper::formatCurrency(tb->getSoDuTaiKhoan(), "VND") << "\n";

    double soTien = InputHelper::getDouble("Nhap so tien nap (VND): ", 10000.0);
    if (std::cin.eof()) return;

    std::cout << "Chon hinh thuc nap:\n"
              << "  [1] " << NapTienConstants::METHOD_SCRATCH_CARD << " (The cao)\n"
              << "  [2] " << NapTienConstants::METHOD_BANKING << " (Ngan hang)\n"
              << "  [3] " << NapTienConstants::METHOD_E_WALLET << " (Vi dien tu)\n";
    int hinhThucChoice = InputHelper::getInt("Nhap lua chon [1-3]: ", 1, 3);
    if (std::cin.eof()) return;
    std::string hinhThuc = (hinhThucChoice == 1) ? NapTienConstants::METHOD_SCRATCH_CARD
                         : (hinhThucChoice == 2) ? NapTienConstants::METHOD_BANKING
                                                 : NapTienConstants::METHOD_E_WALLET;

    std::string ngayNap = InputHelper::getString("Nhap ngay nap (DD/MM/YYYY, 'now' hoac '0' de huy): ");
    if (ngayNap == "0" || std::cin.eof()) {
        std::cout << "[DA HUY] Thao tac nap tien da duoc huy bo.\n";
        return;
    }
    try {
        ngayNap = Date::parse(ngayNap).toString();
    } catch (const std::exception& e) {
        std::cout << "[LOI] " << e.what() << "\n";
        return;
    }

    try {
        NapTien nt(maGD, sdt, ngayNap, soTien, hinhThuc, NapTienConstants::STATUS_SUCCESS);
        napTienStore.add(nt);

        // Cộng tiền trực tiếp vào số dư thuê bao
        ThueBao updated = *tb;
        try {
            updated.congTien(soTien);
            thueBaoStore.update(sdt, updated);
        } catch (const std::exception&) {
            napTienStore.remove(maGD);
            throw;
        }

        std::cout << "[THANH CONG] Da lap phieu nap tien " << maGD << " thanh cong!\n"
                  << "So du moi cua thue bao " << sdt << ": "
                  << DisplayHelper::formatCurrency(updated.getSoDuTaiKhoan(), "VND") << "\n";
    } catch (const std::exception& e) {
        std::cout << "[LOI] Khong the thuc hien nap tien: " << e.what() << "\n";
    }
}

// Hiển thị danh sách phiếu nạp tiền
void NapTienMenu::xemDanhSachPhieu() {
    std::cout << "\n>>> DANH SACH PHIEU NAP TIEN <<<\n";
    if (napTienStore.empty()) {
        std::cout << "[THONG BAO] Danh sach phieu nap tien hien dang trong!\n";
        return;
    }
    DisplayHelper::printTable(napTienStore.getAll());
    std::cout << "Tong so: " << napTienStore.size() << " phieu nap tien.\n";
}

// Tra cứu lịch sử nạp tiền theo số điện thoại
void NapTienMenu::traCuuTheoSoDienThoai() {
    std::cout << "\n>>> TRA CUU LICH SU NAP TIEN THEO SO THUE BAO <<<\n";
    std::string sdt = InputHelper::getPhoneNumber("Nhap so dien thoai: ", false);
    if (std::cin.eof() || sdt.empty()) return;

    auto results = napTienStore.filter([&sdt](const NapTien& nt) {
        return nt.getSoDienThoai() == sdt;
    });

    if (results.empty()) {
        std::cout << "[THONG BAO] Khong co giao dich nap tien nao cua thue bao: " << sdt << "\n";
    } else {
        std::cout << "\nTim thay " << results.size() << " giao dich nap tien:\n";
        DisplayHelper::printTable(results);
    }
}

// Sắp xếp danh sách phiếu nạp theo mã
void NapTienMenu::sapXepDanhSach() {
    std::cout << "\n>>> SAP XEP DU LIEU NAP TIEN <<<\n"
              << "  [1] Ma giao dich nap tien tang dan\n"
              << "  [2] Ma giao dich nap tien giam dan\n"
              << "  [0] Quay lai\n";
    int choice = InputHelper::getInt("Nhap lua chon [0-2]: ", 0, 2);
    if (choice == 0) return;
    try {
        napTienStore.sortById(choice == 1);
        std::cout << "[THANH CONG] Da sap xep va luu du lieu.\n";
    } catch (const std::exception& e) {
        std::cout << "[LOI] Khong the luu thu tu sap xep: " << e.what() << "\n";
    }
    xemDanhSachPhieu();
}

// Hiển thị menu nạp tiền riêng biệt
void NapTienMenu::showMenu() {
    while (true) {
        std::cout << "\n====================================================================\n"
                  << "                      QUAN LY PHIEU NAP TIEN\n"
                  << "====================================================================\n"
                  << "  [1] Lap phieu nap tien (The cao, Banking, Vi)\n"
                  << "  [2] Xem danh sach phieu nap tien\n"
                  << "  [3] Tra cuu lich su nap tiền theo so thue bao\n"
                  << "  [4] Sap xep phieu nap theo ma\n"
                  << "  [0] Quay lai menu chinh\n"
                  << "====================================================================\n";

        int choice = InputHelper::getInt("Nhap lua chon cua ban [0-4]: ", 0, 4);
        if (choice == 0 || std::cin.eof()) {
            break;
        }

        switch (choice) {
            case 1:
                lapPhieuNapTien();
                break;
            case 2:
                xemDanhSachPhieu();
                break;
            case 3:
                traCuuTheoSoDienThoai();
                break;
            case 4:
                sapXepDanhSach();
                break;
            default:
                break;
        }
    }
}
