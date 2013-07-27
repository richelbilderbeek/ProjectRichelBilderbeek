#ifndef QTADDROWCOMMAND_H
#define QTADDROWCOMMAND_H

#include <QUndoCommand>

struct QStandardItemModel;
struct QAbstractItemView;

struct QtAddRowCommand : public QUndoCommand
{
  QtAddRowCommand(
    QStandardItemModel * const model,
    QAbstractItemView * const view);
  void redo();
  void undo();

  private:
  std::string m_text;
  QStandardItemModel * const m_model;
  QAbstractItemView  * const m_view;
};

#endif // QTADDROWCOMMAND_H
