#include <iostream>
#include "lib/shared/fileio.h"
#include "lib/shared/Repository.h"
#include "lib/models/hopdong.h"
#include "lib/models/imei.h"
#include "lib/models/goicuoc.h"
#include "lib/models/thuebao.h"
#include "lib/models/khachhang.h"
#include "lib/models/hoadon.h"
#include "lib/models/naptien.h"
#include "lib/models/GhiCuocGoi.h"
#include "lib/models/khieunai.h"
#include "lib/menus/HopDongMenu.h"
#include "lib/menus/ThietBiIMEIMenu.h"
#include "lib/menus/GoiCuocMenu.h"
#include "lib/menus/ThueBaoMenu.h"
#include "lib/menus/KhachHangMenu.h"
#include "lib/menus/NapTienMenu.h"
#include "lib/menus/HoaDonMenu.h"
#include "lib/shared/InputHelper.h"

namespace MainMenuChoices {
    const int MENU_EXIT = 0;
    const int MENU_KHACHHANG = 1;
    const int MENU_GOICUOC = 2;
    const int MENU_THUEBAO = 3;
    const int MENU_HOPDONG = 4;
    const int MENU_IMEI = 5;
    const int MENU_NAPTIEN = 6;
    const int MENU_HOADON = 7;
}

int main() {
    Repository<HopDong> hopDongStore(FilePaths::HOPDONG_DATA);
    Repository<ThietBiIMEI> imeiStore(FilePaths::IMEI_DATA);
    Repository<GoiCuoc> goiCuocStore(FilePaths::GOICUOC_DATA);
    Repository<ThueBao> thueBaoStore(FilePaths::THUEBAO_DATA);
    Repository<KhachHang> khachHangStore(FilePaths::KHACHHANG_DATA);
    Repository<HoaDon> hoaDonStore(FilePaths::HOADON_DATA);
    Repository<NapTien> napTienStore(FilePaths::NAPTIEN_DATA);
    Repository<CDR> ghiCuocGoiStore(FilePaths::GHICUOCGOI_DATA);
    Repository<KhieuNai> khieuNaiStore(FilePaths::KHIEUNAI_DATA);

    try {
        hopDongStore.loadFromFile();
        imeiStore.loadFromFile();
        goiCuocStore.loadFromFile();
        thueBaoStore.loadFromFile();
        khachHangStore.loadFromFile();
        hoaDonStore.loadFromFile();
        napTienStore.loadFromFile();
        ghiCuocGoiStore.loadFromFile();
        khieuNaiStore.loadFromFile();
    } catch (const std::exception& e) {
        std::cerr << "[LOI] Loi khi tai du lieu ban dau: " << e.what() << "\n";
        return 1;
    }

    KhachHangMenu khachHangMenu(khachHangStore, thueBaoStore, hopDongStore);
    GoiCuocMenu goiCuocMenu(goiCuocStore);
    ThueBaoMenu thueBaoMenu(thueBaoStore, goiCuocStore, khachHangStore);
    HopDongMenu hopDongMenu(hopDongStore, khachHangStore, thueBaoStore, goiCuocStore);
    ThietBiIMEIMenu imeiMenu(imeiStore, thueBaoStore);
    NapTienMenu napTienMenu(napTienStore, thueBaoStore, ghiCuocGoiStore);
    HoaDonMenu hoaDonMenu(hoaDonStore, thueBaoStore, khieuNaiStore);

    while (true) {
        std::cout << "\n====================================================================\n"
                  << "        HE THONG QUAN LY THUE BAO DI DONG VIEN THONG (KTLT)\n"
                  << "                  Hoc vien Cong nghe Buu chinh Vien thong\n"
                  << "====================================================================\n"
                  << "  [" << MainMenuChoices::MENU_KHACHHANG << "] Quan ly Khach hang & SIM eKYC\n"
                  << "  [" << MainMenuChoices::MENU_GOICUOC << "] Quan ly Goi cuoc di dong\n"
                  << "  [" << MainMenuChoices::MENU_THUEBAO << "] Quan ly Thue bao di dong\n"
                  << "  [" << MainMenuChoices::MENU_HOPDONG << "] Quan ly Hop dong dich vu\n"
                  << "  [" << MainMenuChoices::MENU_IMEI << "] Quan ly Thiet bi dau cuoi IMEI\n"
                  << "  [" << MainMenuChoices::MENU_NAPTIEN << "] Quan ly Nap tien & Ban ghi CDR\n"
                  << "  [" << MainMenuChoices::MENU_HOADON << "] Quan ly Hoa don & Khieu nai\n"
                  << "  [" << MainMenuChoices::MENU_EXIT << "] Thoat chuong trinh\n"
                  << "====================================================================\n";

        int choice = InputHelper::getInt("Nhap lua chon cua ban [0-7]: ",
                                         MainMenuChoices::MENU_EXIT,
                                         MainMenuChoices::MENU_HOADON);

        if (choice == MainMenuChoices::MENU_EXIT || std::cin.eof()) {
            // dong bo toan bo du lieu khi thoat
            try {
                hopDongStore.saveToFile();
                imeiStore.saveToFile();
                goiCuocStore.saveToFile();
                thueBaoStore.saveToFile();
                khachHangStore.saveToFile();
                hoaDonStore.saveToFile();
                napTienStore.saveToFile();
                ghiCuocGoiStore.saveToFile();
                khieuNaiStore.saveToFile();
                std::cout << "\n[Luu du lieu] Da dong bo toan bo du lieu he thong thanh cong.\n";
            } catch (const std::exception& e) {
                std::cerr << "\n[CANH BAO] Khong the luu du lieu khi thoat: " << e.what() << "\n";
            }
            std::cout << "Cam on ban da su dung chuong trinh! Tam biet.\n";
            break;
        }

        switch (choice) {
            case MainMenuChoices::MENU_KHACHHANG:
                khachHangMenu.showMenu();
                break;
            case MainMenuChoices::MENU_GOICUOC:
                goiCuocMenu.showMenu();
                break;
            case MainMenuChoices::MENU_THUEBAO:
                thueBaoMenu.showMenu();
                break;
            case MainMenuChoices::MENU_HOPDONG:
                hopDongMenu.showMenu();
                break;
            case MainMenuChoices::MENU_IMEI:
                imeiMenu.showMenu();
                break;
            case MainMenuChoices::MENU_NAPTIEN:
                napTienMenu.showMenu();
                break;
            case MainMenuChoices::MENU_HOADON:
                hoaDonMenu.showMenu();
                break;
            default:
                break;
        }
    }

    return 0;
}
