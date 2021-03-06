/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/QString>
#include "node.h"

namespace simpleParser {
namespace ast {

/// Class that represents text node.
class Text : public Node
{
public:
	/// Constructor.
	/// @param string - value of a literal (with quotes).
	Text(const QString &text)
		: mText(text)
	{
	}

	/// Returns value of a string (with quotes).
	const QString &text() const {
		return mText;
	}

private:
	QString mText;
};

}
}
