/*
 * Fedora Media Writer
 * Copyright (C) 2016 Martin Bříza <mbriza@redhat.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef RELEASE_H
#define RELEASE_H


class ReleaseManager;
class Release;
class Variant;
class Architecture;
class ImageType;

#include <QQmlListProperty>

/**
 * @brief The Release class
 *
 * The class representing a fedora flavor, like for example Workstation or KDE Plasma Desktop spin.
 *
 * It can have multiple versions.
 *
 * @property index the index in the list
 * @property name the name of the release, like "Fedora Workstation"
 * @property summary the summary describing the release - displayed on the main screen
 * @property description the extensive description of the release - displayed on the detail screen
 * @property isLocal true if name is "custom"
 * @property icon path of the icon of this release
 * @property screenshots a list of paths to screenshots (typically HTTP URLs)
 * @property versions a list of available versions of the @ref ReleaseVersion class
 * @property versionNames a list of the names of the available versions
 * @property version the currently selected @ref ReleaseVersion
 * @property versionIndex the index of the currently selected @ref ReleaseVersion
 */
class Release : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString displayName READ displayName CONSTANT)
    Q_PROPERTY(QString summary READ summary CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)

    Q_PROPERTY(bool isLocal READ isLocal CONSTANT)

    Q_PROPERTY(QString icon READ icon CONSTANT)
    Q_PROPERTY(QStringList screenshots READ screenshots CONSTANT)

    Q_PROPERTY(QQmlListProperty<Variant> variants READ variants NOTIFY variantsChanged)
    Q_PROPERTY(Variant* variant READ selectedVariant NOTIFY selectedVariantChanged)
    Q_PROPERTY(int variantIndex READ selectedVariantIndex WRITE setSelectedVariantIndex NOTIFY selectedVariantChanged)
public:
    Release(ReleaseManager *parent, const QString &name, const QString &displayName, const QString &summary, const QString &description, const QString &icon, const QStringList &screenshots);
    Q_INVOKABLE void setLocalFile(const QString &path);
    void updateUrl(const QString &url, Architecture *architecture, ImageType *imageType, const QString &board);
    ReleaseManager *manager();

    QString name() const;
    QString displayName() const;
    QString summary() const;
    QString description() const;
    bool isLocal() const;
    QString icon() const;
    QStringList screenshots() const;

    QQmlListProperty<Variant> variants();
    QList<Variant*> variantList() const;
    Variant *selectedVariant() const;
    int selectedVariantIndex() const;
    void setSelectedVariantIndex(int o);

signals:
    void variantsChanged();
    void selectedVariantChanged();
private:
    QString m_name;
    QString m_displayName;
    QString m_summary;
    QString m_description;
    QString m_icon;
    QStringList m_screenshots;
    QList<Variant *> m_variants;
    int m_selectedVariant = 0;
};

#endif // RELEASE_H