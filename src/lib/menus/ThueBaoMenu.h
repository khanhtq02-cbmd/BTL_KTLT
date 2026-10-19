#ifndef THUEBAOMENU_H
#define THUEBAOMENU_H

#include "Repository.h"
#include "thuebao.h"
#include "goicuoc.h"
#include "khachhang.h"

namespace ThueBaoMenuChoices {
    const int MENU_BACK = 0;
    const int MENU_ADD = 1;
    const int MENU_LIST = 2;
    const int MENU_SEARCH = 3;
    const int MENU_REGISTER_PACKAGE = 4;
    const int MENU_LOCK_UNLOCK = 5;
    const int MENU_TOPUP = 6;
    const int MENU_DELETE = 7;
}

class ThueBaoMenu {
private:
    Repository<ThueBao>& store;
    Repository<GoiCuoc>& goiCuocStore;
    Repository<KhachHang>& khachHangStore;

    void themThueBao();
    void xemDanhSach();
    void timKiemThueBao();
    void dangKyGoiCuoc();
    void khoaMoChieu();
    void napTien();
    void xoaThueBao();

public:
    ThueBaoMenu(Repository<ThueBao>& s, Repository<GoiCuoc>& gs, Repository<KhachHang>& ks)
        : store(s), goiCuocStore(gs), khachHangStore(ks) {}
    void showMenu();
};

#endif // THUEBAOMENU_H
