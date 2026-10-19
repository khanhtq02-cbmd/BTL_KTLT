#ifndef GOICUOCMENU_H
#define GOICUOCMENU_H

#include "Repository.h"
#include "goicuoc.h"

namespace GoiCuocMenuChoices {
    const int MENU_BACK = 0;
    const int MENU_ADD = 1;
    const int MENU_LIST = 2;
    const int MENU_SEARCH = 3;
    const int MENU_SORT = 4;
    const int MENU_UPDATE = 5;
    const int MENU_DELETE = 6;

    const int SORT_BY_PRICE_ASC = 1;
    const int SORT_BY_PRICE_DESC = 2;
    const int SORT_BY_DATA_DESC = 3;
}

class GoiCuocMenu {
private:
    Repository<GoiCuoc>& store;

    void themGoiCuoc();
    void xemDanhSach();
    void timKiemGoiCuoc();
    void sapXepDanhSach();
    void capNhatGoiCuoc();
    void xoaGoiCuoc();

public:
    explicit GoiCuocMenu(Repository<GoiCuoc>& s) : store(s) {}
    void showMenu();
};

#endif // GOICUOCMENU_H
