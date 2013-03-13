//
// Copyright (c) 2013 Ford Motor Company
//

#include "AppMgr/HMIHandler.h"
#include "JSONHandler/JSONRPC2Handler.h"
#include "LoggerHelper.hpp"

namespace NsAppManager
{

    log4cplus::Logger HMIHandler::mLogger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("AppMgrCore"));

    /**
     * \brief Returning class instance
     * \return class instance
     */
    HMIHandler& HMIHandler::getInstance()
    {
        static HMIHandler instance;
        return instance;
    }

    /**
     * \brief set handler ready state
     * \param ready ready state
     */
    void HMIHandler::setReadyState(bool ready)
    {
        if(mJSONRPC2Handler)
        {
            m_bHMIReady = ready;
        }
        else
        {
            LOG4CPLUS_ERROR_EXT(mLogger, " HMIHandler is about to set ready, but is null!");
        }
    }

    /**
     * \brief send notification via associated handler
     * \param command notification to send
     */
    void HMIHandler::sendNotification(const NsRPC2Communication::RPC2Notification *command)
    {
        if(m_bHMIReady)
        {
            if(mJSONRPC2Handler)
            {
                LOG4CPLUS_INFO_EXT(mLogger, " Sending a notification " << command->getMethod());
                mJSONRPC2Handler->sendNotification(command);
            }
        }
        else
        {
            LOG4CPLUS_ERROR_EXT(mLogger, " HMIHandler not ready yet!");
        }
    }

    /**
     * \brief send response via associated handler
     * \param command response to send
     */
    void HMIHandler::sendResponse(const NsRPC2Communication::RPC2Response *command)
    {
        if(m_bHMIReady)
        {
            if(mJSONRPC2Handler)
            {
                LOG4CPLUS_INFO_EXT(mLogger, " Sending a response " << command->getMethod());
                mJSONRPC2Handler->sendResponse(command);
            }
        }
        else
        {
            LOG4CPLUS_ERROR_EXT(mLogger, " HMIHandler not ready yet!");
        }
    }

    /**
     * \brief send request via associated handler
     * \param command request to send
     */
    void HMIHandler::sendRequest(const NsRPC2Communication::RPC2Request *command)
    {
        if(m_bHMIReady)
        {
            if(mJSONRPC2Handler)
            {
                LOG4CPLUS_INFO_EXT(mLogger, " Sending a request " << command->getMethod());
                mJSONRPC2Handler->sendRequest(command);
            }
        }
        else
        {
            LOG4CPLUS_ERROR_EXT(mLogger, " HMIHandler not ready yet!");
        }
    }

    /**
     * \brief set Json RPC2 handler
     * \param handler Json RPC2 handler instance
     */
    void HMIHandler::setJsonRPC2Handler(JSONRPC2Handler *handler)
    {
        if(!handler)
        {
            LOG4CPLUS_ERROR_EXT(mLogger, "A null pointer is being assigned - is this the intent?");
            return;
        }
        mJSONRPC2Handler = handler;
    }

    /**
     * \brief get Json RPC2 handler
     * \return Json RPC2 handler instance
     */
    JSONRPC2Handler *HMIHandler::getJsonRPC2Handler() const
    {
        if(!mJSONRPC2Handler)
        {
            LOG4CPLUS_ERROR_EXT(mLogger, "JSON RPC2 handler hasn't yet been assigned, but an attempt to retrieve it has been made! Face a core dump soon...(((");
        }
        return mJSONRPC2Handler;
    }

    /**
     * \brief Default class constructor
     */
    HMIHandler::HMIHandler()
        :mJSONRPC2Handler(0)
        ,m_bHMIReady(false)
    {
        LOG4CPLUS_INFO_EXT(mLogger, " HMIHandler constructed!");
    }

    /**
     * \brief Copy constructor
     */
    HMIHandler::HMIHandler(const HMIHandler &)
        :mJSONRPC2Handler(0)
        ,m_bHMIReady(false)
    {
    }

}
