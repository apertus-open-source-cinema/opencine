#ifndef OCBACKUPLAYOUT_H
#define OCBACKUPLAYOUT_H

#include <memory>

#include <QWidget>
#include <QQmlContext>

class IBackupPresenter;

namespace Ui {
  class OCBackupLayout;
}

class OCBackupLayout : public QWidget
{
  Q_OBJECT

public:
  explicit OCBackupLayout(QWidget *parent = 0, IBackupPresenter* presenter = nullptr);
  ~OCBackupLayout();

private:
  Ui::OCBackupLayout *ui;

  QQmlContext* _qmlContext;
  IBackupPresenter* _presenter;
};

#endif // OCBACKUPLAYOUT_H
