#include "tgprioritydelegate.h"

tgPriorityDelegate::tgPriorityDelegate(QObject *parent): QStyledItemDelegate(parent) { }

QWidget *tgPriorityDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QSlider* editor = new QSlider(parent);
    editor->setOrientation(Qt::Horizontal);
    editor->setMaximum(100);
    editor->setAutoFillBackground(true);

    return editor;
}

void tgPriorityDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    QSlider * slider = static_cast<QSlider*>(editor);
    slider->setValue(index.data().toInt());

}

void tgPriorityDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSlider * slider = static_cast<QSlider*>(editor);
    model->setData(index, slider->value());
}

void tgPriorityDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

void tgPriorityDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int value = index.data().toInt();
    QStyleOptionProgressBar progressBar;
    progressBar.minimum = 0;
    progressBar.maximum = 100;
    progressBar.rect = option.rect;
    progressBar.progress = value;
    progressBar.text = QString::number(value);
    progressBar.textVisible = true;
    progressBar.textAlignment = Qt::AlignHCenter;

    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBar, painter);
}
