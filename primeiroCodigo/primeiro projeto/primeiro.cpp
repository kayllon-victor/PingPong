#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "primeiro.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<primeiro> reg(_T("primeiro"));
}

// constructor
primeiro::primeiro()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("primeiro.zip")))
    {
        NotifyMissingFile(_T("primeiro.zip"));
    }
}

// destructor
primeiro::~primeiro()
{
}

void primeiro::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
}

void primeiro::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

int primeiro::Execute()
{
    // do your magic ;)
    NotImplemented(_T("primeiro::Execute()"));
    return -1;
}
