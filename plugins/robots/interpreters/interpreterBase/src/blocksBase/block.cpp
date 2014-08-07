#include <interpreterBase/blocksBase/block.h>

using namespace interpreterBase;
using namespace blocksBase;
using namespace qReal;

Block::Block()
	: mNextBlockId(Id())
	, mGraphicalModelApi(nullptr)
	, mLogicalModelApi(nullptr)
	, mGraphicalId(Id())
	, mParser(nullptr)
	, mState(idle)
	, mErrorReporter(nullptr)
	, mRobotModelManager(nullptr)
{
	connect(this, &BlockInterface::done, this, &Block::finishedRunning);
}

void Block::init(Id const &graphicalId
		, GraphicalModelAssistInterface const &graphicalModelApi
		, LogicalModelAssistInterface const &logicalModelApi
		, ErrorReporterInterface * const errorReporter
		, BlockParserInterface * const parser
		, robotModel::RobotModelManagerInterface const &robotModelManager
		)
{
	mGraphicalId = graphicalId;
	mGraphicalModelApi = &graphicalModelApi;
	mLogicalModelApi = &logicalModelApi;
	mErrorReporter = errorReporter;
	mParser = parser;
	mRobotModelManager = &robotModelManager;
}

bool Block::initNextBlocks()
{
	if (id().isNull() || id() == Id::rootId()) {
		error(tr("Control flow break detected, stopping"));
		return false;
	}

	IdList const links = mGraphicalModelApi->graphicalRepoApi().outgoingLinks(id());

	if (links.count() > 1) {
		error(tr("Too many outgoing links"));
		return false;
	}

	if (links.count() == 0) {
		error(tr("No outgoing links, please connect this block to something or use Final Node to end program"));
		return false;
	}

	if (links.count() == 1) {
		Id const nextBlockId = mGraphicalModelApi->graphicalRepoApi().otherEntityFromLink(links[0], id());
		if (nextBlockId.isNull() || nextBlockId == Id::rootId()) {
			error(tr("Outgoing link is not connected"));
			return false;
		}

		mNextBlockId = nextBlockId;
	}

	return true;
}

Id const Block::id() const
{
	return mGraphicalId;
}

void Block::interpret()
{
	// mState == running is not filtered out due to recursions and forks
	if (mState == failed) {
		return;
	}

	mState = running;
	if (initNextBlocks()) {
		run();
	}
}

void Block::setFailedStatus()
{
	mState = failed;
}

void Block::finishedRunning()
{
	mState = idle;
}

QVariant Block::property(QString const &propertyName) const
{
	return property(id(), propertyName);
}

QString Block::stringProperty(QString const &propertyName) const
{
	return stringProperty(id(), propertyName);
}

int Block::intProperty(QString const &propertyName) const
{
	return intProperty(id(), propertyName);
}

bool Block::boolProperty(QString const &propertyName) const
{
	return boolProperty(id(), propertyName);
}

QVariant Block::property(Id const &id, QString const &propertyName) const
{
	Id const logicalId = mGraphicalModelApi->logicalId(id);
	return mLogicalModelApi->propertyByRoleName(logicalId, propertyName);
}

QString Block::stringProperty(Id const &id, QString const &propertyName) const
{
	return property(id, propertyName).toString();
}

int Block::intProperty(Id const &id, QString const &propertyName) const
{
	return property(id, propertyName).toInt();
}

bool Block::boolProperty(Id const &id, QString const &propertyName) const
{
	return property(id, propertyName).toBool();
}

QColor Block::propertyToColor(QString const &property) const
{
	// Qt does not support dark-yellow string color (see QColor::colorNames())
	return property == "darkYellow" ? QColor(Qt::darkYellow) : QColor(property);
}

void Block::error(QString const &message)
{
	mErrorReporter->addError(message, id());
	emit failure();
}

QMap<robotModel::PortInfo, robotModel::DeviceInfo> Block::usedDevices() const
{
	return QMap<robotModel::PortInfo, robotModel::DeviceInfo>();
}

QVariant Block::evaluate(QString const &propertyName)
{
	int position = 0;
	utils::Number *result = mParser->standartBlockParseProcess(stringProperty(propertyName), position, mGraphicalId);
	if (mParser->hasErrors()) {
		mParser->deselect();
		emit failure();
		delete result;
		return QVariant();
	}

	QVariant const value = result->value();
	delete result;
	return value;
}

bool Block::evaluateBool(QString const &propertyName)
{
	int position = 0;
	bool const value = mParser->parseCondition(stringProperty(propertyName), position, mGraphicalId);
	if (mParser->hasErrors()) {
		mParser->deselect();
		emit failure();
	}

	return value;
}

interpreterBase::robotModel::RobotModelInterface &Block::model()
{
	return mRobotModelManager->model();
}

void Block::finishedSteppingInto()
{
}
