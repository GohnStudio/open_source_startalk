#ifndef SNIPSCREEMTOOLBAR_H
#define SNIPSCREEMTOOLBAR_H

#include <QWidget>
#include "ui_snipscreemtoolbar.h"

class SnipScreemToolBar : public QWidget
{
    Q_OBJECT
public:
    enum TOOLTYPE
    {
        SNIP_TOOLBAR_NONE,
        SNIP_TOOLBAR_RECT,
        SNIP_TOOLBAR_RING,
        SNIP_TOOLBAR_PEN,
        SNIP_TOOLBAR_TEXT,
        SNIP_TOOLBAR_ARROW
    };
public:
    SnipScreemToolBar(QWidget *parent = 0);
    ~SnipScreemToolBar();
public:
    // ������Ҫ��������λ�ã��ж��ӹ���������ʾλ�������滹������
    void showSubToolBar();
    // ��ʼ��������
    void initToolBar();

    void setDirect(int d) {m_nDirect=d;};
    int getHeight();
protected slots:
    //  ����༭����ѡȡ����ѡ�еİ�ť��Ҫ<= 0
    void onEditToolSelected(bool checked);
signals:
    void sgColorChange(const QString& colorString);
    void sgPenSizeChange(const int penSize);
    void sgToolSelect(TOOLTYPE type);
    void sgUndo();
    void sgOk();
    void sgCancle();
protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void enterEvent(QEvent *);
protected:
    // ui update
    void setPenSizeStyle(QWidget* pw,bool bselected);
    void setPenColorStyle(QWidget* pRect,QLabel* pContent,QString contentColor,bool bSelected);
    //  �ʴ���Сѡ��
    void onPenSizeChanged (QWidget* pwidget);
    // �ʴ���ɫ
    void onPenColorHovered(QWidget* pwidget,bool hovered);
    void onPenColorSelected(QWidget* pwidget);

private:
    int m_nDirect;
    Ui::SnipScreemToolBar ui;
    QList<QWidget*> m_lstDownPenSize;
    QList<QWidget*> m_lstUpPenSize;

    QList<QWidget*> m_lstDownColorRect;
    QList<QWidget*> m_lstUpColorRect;
    QList<QLabel*> m_lstDownColor;
    QList<QLabel*> m_lstUpColor;

    QList<QString> m_lstColorValue;
    QList<int> m_lstPenSizeValue;

    int m_nCurPensize;
    QString m_strCurColor;
    TOOLTYPE m_tyCurrentType;
};

#endif // SNIPSCREEMTOOLBAR_H
