#ifndef HOADON_MENU_H
#define HOADON_MENU_H

#include "Repository.h"
#include "hoadon.h"
#include "thuebao.h"
#include "khieunai.h"

namespace HoaDonMenuChoices {
    const int MENU_BACK = 0;
    const int MENU_CREATE_INVOICE = 1;
    const int MENU_LIST_INVOICES = 2;
    const int MENU_PAY_INVOICE = 3;
    const int MENU_SEARCH_BY_PHONE = 4;
    const int MENU_ADD_COMPLAINT = 5;
    const int MENU_PROCESS_COMPLAINT = 6;
    const int MENU_LIST_COMPLAINTS = 7;
}

class HoaDonMenu {
private:
    Repository<HoaDon>& hoaDonStore;
    Repository<ThueBao>& thueBaoStore;
    Repository<KhieuNai>& khieuNaiStore;

    void lapHoaDon();
    void xemDanhSachHoaDon();
    void thanhToanHoaDon();
    void traCuuTheoSoDienThoai();
    void tiepNhanKhieuNai();
    void xuLyKhieuNai();
    void xemDanhSachKhieuNai();

public:
    HoaDonMenu(Repository<HoaDon>& hdRepo,
               Repository<ThueBao>& tbRepo,
               Repository<KhieuNai>& knRepo)
        : hoaDonStore(hdRepo), thueBaoStore(tbRepo), khieuNaiStore(knRepo) {}

    void showMenu();
};

#endif // HOADON_MENU_H
