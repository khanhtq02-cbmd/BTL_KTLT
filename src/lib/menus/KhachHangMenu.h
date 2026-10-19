#ifndef KHACHHANG_MENU_H
#define KHACHHANG_MENU_H

#include "Repository.h"
#include "khachhang.h"
#include "thuebao.h"
#include "hopdong.h"

namespace KhachHangMenuChoices {
    const int MENU_BACK = 0;
    const int MENU_ADD = 1;
    const int MENU_LIST = 2;
    const int MENU_SEARCH = 3;
    const int MENU_UPDATE = 4;
    const int MENU_DELETE = 5;
    const int MENU_VIEW_SIMS = 6;

    const int SEARCH_BY_ID = 1;
    const int SEARCH_BY_CCCD = 2;
    const int SEARCH_BY_NAME = 3;
}

class KhachHangMenu {
private:
    Repository<KhachHang>& store;
    Repository<ThueBao>& thueBaoStore;
    Repository<HopDong>& hopDongStore;

    void themKhachHang();
    void xemDanhSach();
    void timKiemKhachHang();
    void capNhatKhachHang();
    void xoaKhachHang();
    void xemDanhSachSIM();

public:
    KhachHangMenu(Repository<KhachHang>& khRepo,
                  Repository<ThueBao>& tbRepo,
                  Repository<HopDong>& hdRepo)
        : store(khRepo), thueBaoStore(tbRepo), hopDongStore(hdRepo) {}

    void showMenu();
};

#endif // KHACHHANG_MENU_H
