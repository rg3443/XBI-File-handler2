#include "cpresenter.h"

CPresenter::CPresenter(QWidget *parent) : QMainWindow(parent)
{

}

void CPresenter::Init()
{
    view = nullptr;
}

void CPresenter::Run()
{
    if(view != nullptr) view = nullptr;
    view = new CView(&model);
    view->show();
}
