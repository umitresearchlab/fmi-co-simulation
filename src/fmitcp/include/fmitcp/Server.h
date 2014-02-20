#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#define lw_import
#include <lacewing.h>
#define FMILIB_BUILDING_LIBRARY
#include <fmilib.h>
#include "EventPump.h"
#include "Logger.h"
#include "fmitcp.pb.h"

using namespace std;

namespace fmitcp {

  class Server {

  private:
    Logger m_logger;
    lw_server m_server;
    bool m_sendDummyResponses;

  protected:
    EventPump * m_pump;
    string m_fmuPath;
    // FMU logging level
    jm_log_level_enu_t m_logLevel;
    bool m_debugLogging;
    jm_callbacks m_jmCallbacks;
    // Directory for the unpacked FMU
    string m_workingDir;
    fmi_import_context_t* m_context;
    fmi_version_enu_t m_version;
    // FMI 2.0
    fmi2_import_t* m_fmi2Instance;
    fmi2_callback_functions_t m_fmi2CallbackFunctions;
    fmi2_import_variable_list_t* m_fmi2Variables;


    string m_instanceName;
    string m_fmuLocation;
  public:
    Server(string fmuPath, bool debugLogging, jm_log_level_enu_t logLevel, EventPump *pump);
    Server(string fmuPath, bool debugLogging, jm_log_level_enu_t logLevel, EventPump *pump, const Logger &logger);
    virtual ~Server();

    void init(EventPump *pump);
    /// To be implemented in subclass
    virtual void onClientConnect();
    /// To be implemented in subclass
    virtual void onClientDisconnect();
    /// To be implemented in subclass
    virtual void onError(string message);

    void clientConnected(lw_client c);
    void clientDisconnected(lw_client c);
    void clientData(lw_client c, const char *data, size_t size);
    void error(lw_server s, lw_error err);

    void host(string host, long port);

    /// Set to true to start ignoring the local FMU and just send back dummy responses. Good for debugging the protocol.
    void sendDummyResponses(bool);

    void sendMessage(lw_client c, fmitcp_proto::fmitcp_message* message);

    Logger* getLogger() {return &m_logger;}
    void setLogger(const Logger &logger);
  };

};

#endif
