#include "communicationservice.h"
#include "udpchannel.h"
#include "commchannel.h"
#include "communication_define.h"
#include "communication_equipment.h"
#include "ttccombination.h"
#include "ttcfrontcomputer.h"
#include <QDebug>

int CommunicationService::sendMessage(const QString &channelId, const QByteArray &data)
{
    if( !m_channels.contains(channelId) ) return 0;

    CommunicationServiceBase *communicationBase = m_channels[channelId];
    if( !communicationBase ) return 0;

    return communicationBase->sendData(data);
}

int CommunicationService::sendMessage(const QString &channelId, const QByteArray &data, QString sendIP)
{
    if( !m_channels.contains(channelId) ) return 0;

    CommunicationServiceBase *communicationBase = m_channels[channelId];
    if( !communicationBase ) return 0;

    return communicationBase->sendData(data, sendIP);
}

void CommunicationService::initCommunication()
{
    QDomDocument document;
    QDomElement root;

    QFile file(m_configPath);
    QString errorMessage;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    if (!document.setContent(&file, false, &errorMessage))
    {
        file.close();
        return;
    }

    file.close();

    root = document.documentElement();
    QDomNode channelNode = root.firstChild();
    while(!channelNode.isNull())
    {
        if( channelNode.nodeName() != CHANNEL_NODE_NAME )
        {
            channelNode = channelNode.nextSibling();
            continue;
        }

        CommunicationServiceBase *communicationBase = createChannel(channelNode);

        if( communicationBase ) m_channels[communicationBase->getAttr(CHANNEL_ID)] = communicationBase;

        channelNode = channelNode.nextSibling();
    }
}

CommunicationServiceBase *CommunicationService::createChannel(const ChannelAttributes &attrs)
{
    CommunicationServiceBase *channelBase = NULL;
    ChannelType channelType = CHANNEL_TYPE_NONE;

    if( attrs.contains(CHANNEL_TYPE) ) channelType = (ChannelType)attrs[CHANNEL_TYPE].toInt();
    else return NULL;

    {
        std::string id = "";
        if( attrs.contains(CHANNEL_ID) ) id = attrs[CHANNEL_ID].toStdString();

        if( CHANNEL_ID_Equipment == id )
        {
            channelBase = new Communication_Equipment(m_context,attrs, this);
        }
        else if(CHANNEL_ID_TTCCombination == id)
        {
            channelBase = new TTCCombination(m_context,attrs, this);
        }
        else if(CHANNEL_ID_TTCFrontCompter == id)
        {
            channelBase = new TTCFrontComputer(m_context,attrs, this);
        }

        if( channelBase )
        {
            channelBase->start();
        }
    }

    return channelBase;
}

CommunicationServiceBase *CommunicationService::createChannel(const QDomNode &configNode)
{
    ChannelAttributes attrs;
    analysisAttr(configNode, attrs);

    return createChannel(attrs);
}

void CommunicationService::analysisAttr(const QDomNode &configNode, ChannelAttributes &attrs)
{
    if( configNode.nodeName() != CHANNEL_NODE_NAME ) return;

    //解析本节点
    QDomElement configElement = configNode.toElement();
    QDomNamedNodeMap maps = configElement.attributes();
    for(int i=0; i<maps.length(); ++i)
    {
        attrs[maps.item(i).nodeName()] = maps.item(i).nodeValue();
    }

    QDomNode childNode = configNode.firstChild();

    while( !childNode.isNull() )
    {
        analysisChildAttr(childNode, attrs);

        childNode = childNode.nextSibling();
    }
}


void CommunicationService::analysisChildAttr(const QDomNode &configNode, ChannelAttributes &attrs)
{
    //解析本节点
    QDomElement configElement = configNode.toElement();
    QDomNamedNodeMap maps = configElement.attributes();
    for(int i=0; i<maps.length(); ++i)
    {
        attrs[maps.item(i).nodeName()] = maps.item(i).nodeValue();
    }

    QDomNode childNode = configNode.firstChild();

    while( !childNode.isNull() )
    {
        analysisChildAttr(childNode, attrs);

        childNode = childNode.nextSibling();
    }
}

void CommunicationService::stop()
{
    for (auto &channel : m_channels)
    {
        channel->stop();
    }
}

CommunicationServiceBase *CommunicationService::getCommunication(const QString &channelId)
{
    if( !m_channels.contains(channelId) ) return 0;

    CommunicationServiceBase *communicationBase = m_channels[channelId];

    return communicationBase;
}

CommunicationService::CommunicationService(const QString &path, BundleContext context)
    : m_context(context)
    , m_configPath(path)
{
    initCommunication();
}

CommunicationService::~CommunicationService() {}

BundleContext CommunicationService::getBundleContext()
{
    return m_context;
}
