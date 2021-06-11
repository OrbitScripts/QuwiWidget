#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QJsonObject>

class Project {
public:
  Project();

  void fillFromJsonObject(const QJsonObject& json);

  int id;
  QString name;
  QString uid;
  QString logoUrl;
  int position;
  bool isActive;
  bool hasStarred;
};

#endif // PROJECT_H
