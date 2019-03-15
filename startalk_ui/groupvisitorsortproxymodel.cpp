#include "groupvisitorsortproxymodel.h"
#include "GroupVisitorMVD.h"
GroupVisitorSortProxyModel::GroupVisitorSortProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    setFilterRole(Qt::DisplayRole);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

GroupVisitorSortProxyModel::~GroupVisitorSortProxyModel()
{

}

bool GroupVisitorSortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    int leftPresence  = left.data(VisitorItem::Presence).toInt();
    int rightPresence = right.data(VisitorItem::Presence).toInt();

    int leftAff = left.data(VisitorItem::UserAffiliationType).toInt();
    int rightAff = right.data(VisitorItem::UserAffiliationType).toInt();

    QString leftGroupName = left.data(VisitorItem::NickNamePY).toString();
    QString rightGroupName = right.data(VisitorItem::NickNamePY).toString();
   

    // 0 Ⱥ��/����Ա��ǰ��
    // 1 ���߰�������������
    // 2 �����ߵİ�����������

    if (leftAff!=rightAff)
    {
        return leftAff>rightAff;
    }
    else if(leftPresence != rightPresence) // ���ߵ���ǰ��
    {
        return leftPresence>rightPresence;
    }
    else
    {
        return (leftGroupName.compare(rightGroupName) < 0);
    }
}

bool GroupVisitorSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    if(!filterRegExp().isEmpty())
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    return true;
}
