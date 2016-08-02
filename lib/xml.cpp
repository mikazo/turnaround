#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOM.hpp>

#include "xml.h"
#include "HostRunTask.h"
#include "HostSetDirTask.h"
#include "HostCreateDirTask.h"
#include "HostFileCopyTask.h"
#include "HostDeleteTask.h"
#include "VMFileCopyTask.h"
#include "VMRevertTask.h"
#include "VMRunTask.h"

using namespace xercesc;

static bool GetTagValue( DOMNode* parentNode, const std::string& tagName, std::string& tagValue )
{
    bool result = false;
    DOMNodeList* childNodes = NULL;
    DOMNode* childNode = NULL;
    std::string childNodeName;

    if( parentNode )
    {
        childNodes = parentNode->getChildNodes();

        for( int i = 0; i < childNodes->getLength() && !result; i++ )
        {
            childNode = childNodes->item( i );
            if( childNode )
            {
                childNodeName = std::string( XMLString::transcode( childNode->getNodeName() ) );
                if( tagName == childNodeName )
                {
                    tagValue = std::string( XMLString::transcode( childNode->getFirstChild()->getNodeValue() ) );

                    result = true;
                }
            }
            else
            {
                std::cout << "Invalid child node." << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Invalid parent node." << std::endl;
    }

    return result;
}

static bool ParseNode( DOMNode* node, std::vector<Task*>& tasks )
{
    bool result = false;
    DOMNamedNodeMap* attributeMap = NULL;
    DOMNode* typeNode = NULL;
    std::string nodeName( XMLString::transcode( node->getNodeName() ) );
    std::string typeNodeName;
    std::string typeStr;
    Task* newTask = NULL;
    std::string directoryValue;
    std::string commandValue;
    std::string vmxPath;
    std::string snapshotValue;
    std::string sourceValue;
    std::string destinationValue;
    std::string copyTypeStr;
    std::string waitValue;
    std::string nameValue;
    std::string usernameValue;
    std::string passwordValue;
    std::string pathValue;

    if( "task" == nodeName )
    {
        attributeMap = node->getAttributes();
        if( attributeMap )
        {
            typeNode = attributeMap->item( 0 );
            if( typeNode )
            {
                typeNodeName = std::string( XMLString::transcode( typeNode->getNodeName() ) );
                if( "type" == typeNodeName )
                {
                    typeStr = std::string( XMLString::transcode( typeNode->getNodeValue() ) );

                    if( "host_set_current_directory" == typeStr )
                    {
                        if( GetTagValue( node, "directory", directoryValue ) )
                        {
                            newTask = new HostSetDirTask( directoryValue );
                            if( newTask )
                            {
                                tasks.push_back( newTask );
                                result = true;

                                std::cout << "HostSetDirTask created." << std::endl;
                            }
                        }
                    }
                    else if( "host_create_directory" == typeStr )
                    {
                        if( GetTagValue( node, "directory", directoryValue ) )
                        {
                            newTask = new HostCreateDirTask( directoryValue );
                            if( newTask )
                            {
                                tasks.push_back( newTask );
                                result = true;

                                std::cout << "HostCreateDirTask created." << std::endl;
                            }
                        }
                    }
                    else if( "host_run_program" == typeStr )
                    {
                        if( GetTagValue( node, "command", commandValue ) )
                        {
                            newTask = new HostRunTask( commandValue );
                            if( newTask )
                            {
                                tasks.push_back( newTask );
                                result = true;

                                std::cout << "HostRunTask created." << std::endl;
                            }
                        }
                    }
                    else if( "host_file_copy" == typeStr )
                    {
                        if( GetTagValue( node, "source", sourceValue ) )
                        {
                            if( GetTagValue( node, "destination", destinationValue ) )
                            {
                                newTask = new HostFileCopyTask( sourceValue, destinationValue );
                                if( newTask )
                                {
                                    tasks.push_back( newTask );
                                    result = true;

                                    std::cout << "HostFileCopyTask created." << std::endl;
                                }
                            }
                        }
                    }
                    else if( "host_delete" == typeStr )
                    {
                        if( GetTagValue( node, "path", pathValue ) )
                        {
                            newTask = new HostDeleteTask( pathValue );
                            if( newTask )
                            {
                                tasks.push_back( newTask );
                                result = true;

                                std::cout << "HostDeleteTask created." << std::endl;
                            }
                        }
                    }
                    else if( "vm_revert" == typeStr )
                    {
                        if( GetTagValue( node, "vmxpath", vmxPath ) )
                        {
                            if( GetTagValue( node, "name", nameValue ) )
                            {
                                newTask = new VMRevertTask( vmxPath, nameValue );
                                if( newTask )
                                {
                                    tasks.push_back( newTask );
                                    result = true;

                                    std::cout << "VMRevertTask created." << std::endl;
                                }
                            }
                        }
                    }
                    else if( "vm_file_copy" == typeStr )
                    {
                        if( GetTagValue( node, "vmxpath", vmxPath ) &&
                            GetTagValue( node, "username", usernameValue ) &&
                            GetTagValue( node, "password", passwordValue ) &&
                            GetTagValue( node, "type", copyTypeStr ) &&
                            GetTagValue( node, "source", sourceValue ) &&
                            GetTagValue( node, "destination", destinationValue ) )
                        {
                            if( "HostToVM" == copyTypeStr )
                            {
                                newTask = new VMFileCopyTask( vmxPath, usernameValue, passwordValue, HOST_TO_VM, sourceValue, destinationValue );
                            }
                            else if( "VMToHost" == copyTypeStr )
                            {
                                newTask = new VMFileCopyTask( vmxPath, usernameValue, passwordValue, VM_TO_HOST, sourceValue, destinationValue );
                            }

                            if( newTask )
                            {
                                tasks.push_back( newTask );
                                result = true;
                                
                                std::cout << "VMFileCopyTask created." << std::endl;
                            }
                        }
                    }
                    else if( "vm_run_program" == typeStr )
                    {
                        if( GetTagValue( node, "vmxpath", vmxPath ) &&
                            GetTagValue( node, "username", usernameValue ) &&
                            GetTagValue( node, "password", passwordValue ) &&
                            GetTagValue( node, "command", commandValue ) &&
                            GetTagValue( node, "wait", waitValue ) )
                        {
                            if( "true" == waitValue )
                            {
                                newTask = new VMRunTask( vmxPath, usernameValue, passwordValue, commandValue, true );
                            }
                            else if( "false" == waitValue )
                            {
                                newTask = new VMRunTask( vmxPath, usernameValue, passwordValue, commandValue, false );
                            }

                            if( newTask )
                            {
                                tasks.push_back( newTask );
                                result = true;

                                std::cout << "VMRunTask created." << std::endl;
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Unsupported task type." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Invalid type attribute." << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to get type attribute." << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get task node attributes." << std::endl;
        }
    }
    else if( "#text" == nodeName || "#comment" == nodeName )
    {
        // Empty text node or comment, skip it.
        result = true;
    }
    else
    {
        std::cout << "Invalid task node name: " << nodeName << std::endl;
    }

    return result;
}

bool ParseXML( const std::string& filename, std::vector<Task*>& tasks )
{
    bool result = false;
    XercesDOMParser* parser = NULL;
    ErrorHandler* errorHandler = NULL;
    DOMDocument* document = NULL;
    DOMElement* rootElement = NULL;
    DOMNodeIterator* documentIterator = NULL;
    DOMNode* rootNode = NULL;
    DOMNodeList* taskNodes = NULL;
    DOMNode* currentNode = NULL;
    std::string nodeName;

    try
    {
        XMLPlatformUtils::Initialize();

        parser = new XercesDOMParser();
        if( parser )
        {
            parser->setValidationScheme( XercesDOMParser::Val_Always );

            errorHandler = ( ErrorHandler* ) new HandlerBase();
            if( errorHandler )
            {
                parser->setErrorHandler( errorHandler );

                parser->parse( filename.c_str() );

                document = parser->getDocument();
                if( document )
                {
                    rootElement = document->getDocumentElement();
                    if( rootElement )
                    {
                        documentIterator = document->createNodeIterator( rootElement,
                                                                         DOMNodeFilter::SHOW_ELEMENT,
                                                                         NULL,
                                                                         true );
                        if( documentIterator )
                        {
                            rootNode = documentIterator->nextNode();
                            if( rootNode )
                            {
                                nodeName = std::string( XMLString::transcode( rootNode->getNodeName() ) );
                                if( "turnaround" == nodeName )
                                {
                                    taskNodes = rootNode->getChildNodes();
                                    if( taskNodes )
                                    {
                                        result = true;

                                        for( int i = 0; i < taskNodes->getLength() && result; i++ )
                                        {
                                            currentNode = taskNodes->item( i );
                                            if( currentNode )
                                            {
                                                result = ParseNode( currentNode, tasks );
                                            }
                                            else
                                            {
                                                result = false;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "Failed to create task iterator." << std::endl;
                                    }
                                }
                                else
                                {
                                    std::cout << "Invalid root node name." << std::endl;
                                }
                            }
                            else
                            {
                                std::cout << "Failed to get root node." << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Failed to create iterator." << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Failed to get root element." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Failed to get document." << std::endl;
                }

                delete errorHandler;
            }

            delete parser;
        }
    }
    catch( const XMLException& exception )
    {
    }

    XMLPlatformUtils::Terminate();

    return result;
}

