#ifndef LINKLABEL_H
#define LINKLABEL_H

#include <QObject>
#include <QLabel>

class LinkLabel : public QLabel {
  Q_OBJECT
public:
  explicit LinkLabel(QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());

protected:
  void enterEvent(QEvent* event);
  void leaveEvent(QEvent* event);
};

#endif // LINKLABEL_H
