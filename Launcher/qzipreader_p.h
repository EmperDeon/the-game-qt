/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QZIPREADER_H
#define QZIPREADER_H
#include <QtCore>

QT_BEGIN_NAMESPACE

class QZipReaderPrivate;

class Q_GUI_EXPORT QZipReader {
	QZipReaderPrivate *d;
	Q_DISABLE_COPY(QZipReader)

public:

	struct Q_GUI_EXPORT FileInfo {
		QString filePath;
		uint isDir : 1;
		uint isFile : 1;
		uint isSymLink : 1;
		QFile::Permissions permissions;
		uint crc;
		qint64 size;
		QDateTime lastModified;
		void *d;

		FileInfo();
		FileInfo(const FileInfo &other);
		~FileInfo();

		FileInfo &operator=(const FileInfo &other);
		bool isValid() const;
	};
	enum Status {
		NoError,
		FileReadError,
		FileOpenError,
		FilePermissionsError,
		FileError
	};

	explicit QZipReader(const QString &fileName, QIODevice::OpenMode mode = QIODevice::ReadOnly);
	explicit QZipReader(QIODevice *device);
	~QZipReader();

	QIODevice*      device()                                  const;
	bool            isReadable()                              const;
	bool            exists()                                  const;
	QList<FileInfo> fileInfoList()                            const;
	int             count()                                   const;
	FileInfo        entryInfoAt(int index)                    const;
	QByteArray      fileData(const QString &fileName)         const;

	bool            extractAll(const QString &destinationDir) const;
	Status          status()                                  const;
	void            close();

};

QT_END_NAMESPACE

#endif // QZIPREADER_H
