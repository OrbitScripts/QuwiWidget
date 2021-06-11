#include "NetworkManager.h"

#include <QNetworkReply>

#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
  : QObject(parent)
{
  connect(&m_networkManager, &QNetworkAccessManager::finished,
          this, &NetworkManager::onReplyResponce);
}

void NetworkManager::loginRequest(const QString& login, const QString& password) {
  QNetworkRequest request(m_loginUrl);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  QString jsonData = QString("{\"email\": \"%1\", \"password\": \"%2\"}").arg(login, password);
  m_networkManager.post(request, jsonData.toUtf8());
}

void NetworkManager::logoutRequest() {
  QNetworkRequest request(m_logoutUrl);
  QString bearerToken = QString("Bearer %1").arg(m_token);
  request.setRawHeader("Authorization", bearerToken.toUtf8());
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  QString jsonData = QString("{\"anywhere\": \"true\"}");
  m_networkManager.post(request, jsonData.toUtf8());
}

void NetworkManager::projectsRequest() {
  QNetworkRequest request(m_projectUrl);
  QString bearerToken = QString("Bearer %1").arg(m_token);
  request.setRawHeader("Authorization", bearerToken.toUtf8());
  m_networkManager.get(request);
}

QStringList NetworkManager::getProjects() const {
  QStringList projects;
  foreach (const Project& value, m_projects) {
    projects.append(value.name);
  }
  return projects;
}

void NetworkManager::onReplyResponce(QNetworkReply* reply) {
  QString responce = reply->readAll();
  qDebug() << responce;

  QString errorFromJson;
  if (!responce.isEmpty()) {
    QJsonDocument json = QJsonDocument::fromJson(responce.toUtf8());
    QJsonObject jsonRootObject = json.object();

    if (reply->url() == m_loginUrl) {
      QJsonValue token = jsonRootObject.value("token");
      if (!token.isUndefined()) {
        m_token = token.toString();
      }
    } else if (reply->url() == m_projectUrl) {
      QJsonArray jsonProjects = jsonRootObject["projects"].toArray();

      foreach (const QJsonValue& value, jsonProjects) {
        Project project;
        project.fillFromJsonObject(value.toObject());
        m_projects.append(project);
      }
      emit projectsChanged();
    } else if (reply->url() == m_logoutUrl) {
      m_projects.clear();
      emit projectsChanged();
    }

    QJsonValue firstErrors = jsonRootObject["first_errors"];
    if (!firstErrors.isUndefined()) {
      QJsonObject firstErrorsObject = firstErrors.toObject();
      errorFromJson += firstErrorsObject["email"].toString();
      errorFromJson += firstErrorsObject["password"].toString();
    }
  }

  int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  QString errorString = (reply->error() != QNetworkReply::NoError && statusCode != 417) ? reply->errorString() : "";
  if (errorString.isEmpty() && !errorFromJson.isEmpty()) {
    errorString = errorFromJson;
  }

  emit finishRequest(reply->url().toString(), errorString);
  reply->deleteLater();
}

const QString& NetworkManager::projectUrl() const {
  return m_projectUrl;
}

const QString& NetworkManager::logoutUrl() const {
  return m_logoutUrl;
}

const QString& NetworkManager::loginUrl() const {
  return m_loginUrl;
}
