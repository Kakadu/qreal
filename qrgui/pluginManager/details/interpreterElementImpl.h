#pragma once

#include <QtCore/QMap>
#include <QtWidgets/QWidget>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QRectF>
#include <QtCore/QPointF>
#include <QtGui/QPainter>

#include <qrkernel/ids.h>
#include <qrrepo/repoApi.h>

#include "editorPluginInterface/elementImpl.h"
#include "editorPluginInterface/labelInterface.h"
#include "editorPluginInterface/elementRepoInterface.h"

namespace qReal {

typedef QPair<QPair<qReal::Id, qReal::Id>, QPair<bool, qReal::Id> > PossibleEdge;
typedef QPair<QPair<QString, QString>, QPair<bool, QString> > StringPossibleEdge;
typedef QPair<bool, qReal::Id> PossibleEdgeType;

struct EdgeLabel {
	QString labelText;
	QString labelType;
	LabelInterface* title;

	EdgeLabel(QString const &labelText_, QString const &labelType_, LabelInterface* title_)
		: labelText(labelText_), labelType(labelType_), title(title_)
	{}
};

struct NodeLabel {
	QString textBinded;
	QString center;
	LabelInterface* title;

	NodeLabel(QString const &textBinded_, QString const &center_, LabelInterface* title_)
		: textBinded(textBinded_), center(center_), title(title_)
	{}
};

/// This class is for implementation the graphical representation of element
class InterpreterElementImpl : public ElementImpl
{
public:
	InterpreterElementImpl(qrRepo::RepoApi *repo, Id const &metaId);
	void init(QRectF &contents, PortFactoryInterface const &portFactory, QList<PortInterface *> &ports
			, LabelFactoryInterface &labelFactory, QList<LabelInterface *> &labels) override;
	void init(LabelFactoryInterface &labelFactory, QList<LabelInterface *> &labels) override;

	QUrl qmlUrl() const override;

	void updateData(ElementRepoInterface *repo) const override;
	bool isNode() const override;
	bool isResizeable() const override;
	Qt::PenStyle getPenStyle() const override;
	int getPenWidth() const override;
	QColor getPenColor() const override;
	void drawStartArrow(QPainter *painter) const override;
	void drawEndArrow(QPainter *painter) const override;

	bool isDividable() const override;

	/*Container properties*/
	bool hasContainerProperty(QString const &property) const;
	bool isContainer() const override;
	bool isSortingContainer() const override;
	QVector<int> sizeOfForestalling() const override;
	int sizeOfChildrenForestalling() const override;
	bool hasMovableChildren() const override;
	bool minimizesToChildren() const override;
	bool maximizesChildren() const override;

	QStringList fromPortTypes() const override;
	QStringList toPortTypes() const override;

	enums::linkShape::LinkShape shapeType() const override;

	bool isPort() const override;
	bool hasPin() const override;

	bool createChildrenFromMenu() const override;

	QList<double> border() const override;

	QStringList bonusContextMenuFields() const override;
	void updateRendererContent(QString const &shape) override;

private:
	void initPointPorts(PortFactoryInterface const &factory, QList<PortInterface *> &ports
			, int const &width, int const &height);
	void initLinePorts(PortFactoryInterface const &factory, QList<PortInterface *> &ports
			, int const &width, int const &height);
	void initLabels(int const &width, int const &height, LabelFactoryInterface &factory, QList<LabelInterface*> &titles);
	QVector<int> getSizeOfContainerProperty(QString const &property) const;
	QStringList getListOfStr(QString const &labelText) const;
	QString getResultStr(QStringList const &list, ElementRepoInterface *repo) const;
	void drawArrow(QPainter *painter, QString const &type) const;

	enums::linkShape::LinkShape shapeTypeByString(QString const &type) const;

	qrRepo::RepoApi *mEditorRepoApi;  // Doesn't have ownership.
	Id mId;
	QDomDocument mGraphics;
	QList<NodeLabel> mNodeLabels;
	QList<EdgeLabel> mEdgeLabels;
};
}

