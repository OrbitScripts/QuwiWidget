#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>

#include "DataLayer/Project.h"

class NetworkManager : public QObject {
  Q_OBJECT

  Q_PROPERTY(QStringList projects READ getProjects NOTIFY projectsChanged)

public:
  explicit NetworkManager(QObject *parent = nullptr);

  Q_INVOKABLE void loginRequest(const QString& login, const QString& password);
  Q_INVOKABLE void logoutRequest();
  Q_INVOKABLE void projectsRequest();

  QStringList getProjects() const;

  const QString& loginUrl() const;
  const QString& logoutUrl() const;
  const QString& projectUrl() const;

signals:
  void finishRequest(const QString& url, const QString& error);
  void projectsChanged();

private slots:
  void onReplyResponce(QNetworkReply* reply);

private:
  QNetworkAccessManager m_networkManager;
  QString m_token;
  QList<Project> m_projects;

  const QString m_host = "https://api.quwi.com/v2";
  const QString m_loginUrl = m_host + "/auth/login";
  const QString m_logoutUrl = m_host + "/auth/logout";
  const QString m_projectUrl = m_host + "/projects";
};

#endif // NETWORKMANAGER_H
