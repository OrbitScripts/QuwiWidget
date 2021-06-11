#include "Project.h"

Project::Project() :
  id(-1),
  name(),
  uid(),
  logoUrl(),
  position(-1),
  isActive(false),
  hasStarred(false)
{

}

void Project::fillFromJsonObject(const QJsonObject& json) {
  id = json.value("id").toInt();
  name = json.value("name").toString();
  uid = json.value("uid").toString();
  logoUrl = json.value("logo_url").toString();
  position = json.value("position").toInt();
  isActive = (json.value("is_active").toInt() == 1);
  hasStarred = json.value("has_starred").toBool();
}
