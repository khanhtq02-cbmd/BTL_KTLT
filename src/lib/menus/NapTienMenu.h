#ifndef NAPTIEN_MENU_H
#define NAPTIEN_MENU_H

#include "Repository.h"
#include "naptien.h"
#include "thuebao.h"
#include "cdr.h"

namespace NapTienMenuChoices {
    const int MENU_BACK = 0;
    const int MENU_TOPUP = 1;
    const int MENU_LIST_VOUCHERS = 2;
    const int MENU_SEARCH_BY_PHONE = 3;
    const int MENU_ADD_CDR = 4;
    const int MENU_LIST_CDR = 5;
}

class NapTienMenu {
private:
    Repository<NapTien>& napTienStore;
    Repository<ThueBao>& thueBaoStore;
    Repository<CDR>& cdrStore;

    void lapPhieuNapTien();
    void xemDanhSachPhieu();
    void traCuuTheoSoDienThoai();
    void ghiNhanCDR();
    void xemDanhSachCDR();

public:
    NapTienMenu(Repository<NapTien>& ntRepo,
                Repository<ThueBao>& tbRepo,
                Repository<CDR>& cRepo)
        : napTienStore(ntRepo), thueBaoStore(tbRepo), cdrStore(cRepo) {}

    void showMenu();
};

#endif // NAPTIEN_MENU_H
