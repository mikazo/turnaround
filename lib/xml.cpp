#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOM.hpp>

#include "xml.h"
#include "HostRunTask.h"
#include "HostSetDirTask.h"
#include "VMFileCopyTask.h"
#include "VMRevertTask.h"
#include "VMRunTask.h"

using namespace xercesc;

static bool ParseNode( DOMNode* node, std::vector<Task*>& tasks )
{
    bool result = false;
    DOMNamedNodeMap* attributeMap = NULL;
    DOMNode* typeNode = NULL;
    std::string nodeName( XMLString::transcode( node->getNodeName() ) );
    std::string typeNodeName;
    std::string typeStr;
    Task* newTask = NULL;
    DOMNode* childNode1 = NULL;
    DOMNode* childNode2 = NULL;
    std::string childNodeName1;
    std::string childNodeName2;
    std::string childNodeValue1;
    std::string childNodeValue2;

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
                        childNode1 = node->getChildNodes()->item( 1 );
                        if( childNode1 )
                        {
                            childNodeName1 = std::string( XMLString::transcode( childNode1->getNodeName() ) );
                            if( "directory" == childNodeName1 )
                            {
                                childNodeValue1 = std::string( XMLString::transcode( childNode1->getFirstChild()->getNodeValue() ) );
                                newTask = new HostSetDirTask( childNodeValue1 );
                                if( newTask )
                                {
                                    tasks.push_back( newTask );
                                    result = true;
                                }
                            }
                            else
                            {
                                std::cout << "Invalid child node for type " << typeStr << ": " << childNodeName1 << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Failed to find first child node for type " << typeStr << std::endl;
                        }
                    }
                    else if( "host_run_program" == typeStr )
                    {
                        childNode1 = node->getChildNodes()->item( 1 );
                        if( childNode1 )
                        {
                            childNodeName1 = std::string( XMLString::transcode( childNode1->getNodeName() ) );
                            if( "command" == childNodeName1 )
                            {
                                childNodeValue1 = std::string( XMLString::transcode( childNode1->getFirstChild()->getNodeValue() ) );
                                newTask = new HostRunTask( childNodeValue1 );
                                if( newTask )
                                {
                                    tasks.push_back( newTask );
                                    result = true;
                                }
                            }
                            else
                            {
                                std::cout << "Invalid child node for type " << typeStr << ": " << childNodeName1 << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Failed to find first child node for type " << typeStr << std::endl;
                        }
                    }
                    else if( "vm_revert" == typeStr )
                    {
                        childNode1 = node->getChildNodes()->item( 1 );
                        if( childNode1 )
                        {
                            childNodeName1 = std::string( XMLString::transcode( childNode1->getNodeName() ) );
                            if( "name" == childNodeName1 )
                            {
                                childNodeValue1 = std::string( XMLString::transcode( childNode1->getFirstChild()->getNodeValue() ) );

                                childNode2 = node->getChildNodes()->item( 3 );
                                if( childNode2 )
                                {
                                    childNodeName2 = std::string( XMLString::transcode( childNode2->getNodeName() ) );
                                    if( "snapshot" == childNodeName2 )
                                    {
                                        childNodeValue2 = std::string( XMLString::transcode( childNode2->getFirstChild()->getNodeValue() ) );

                                        newTask = new VMRevertTask( childNodeValue1, childNodeValue2 );
                                        if( newTask )
                                        {
                                            tasks.push_back( newTask );
                                            result = true;
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "Invalid child node for type " << typeStr << ": " << childNodeName2 << std::endl;
                                    }
                                }
                            }
                            else
                            {
                                std::cout << "Invalid child node for type " << typeStr << ": " << childNodeName1 << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Failed to find first child node for type " << typeStr << std::endl;
                        }
                    }
                    else if( "vm_file_copy" == typeStr )
                    {
                        childNode1 = node->getChildNodes()->item( 1 );
                        if( childNode1 )
                        {
                            childNodeName1 = std::string( XMLString::transcode( childNode1->getNodeName() ) );
                            if( "source" == childNodeName1 )
                            {
                                childNodeValue1 = std::string( XMLString::transcode( childNode1->getFirstChild()->getNodeValue() ) );

                                childNode2 = node->getChildNodes()->item( 3 );
                                if( childNode2 )
                                {
                                    childNodeName2 = std::string( XMLString::transcode( childNode2->getNodeName() ) );
                                    if( "destination" == childNodeName2 )
                                    {
                                        childNodeValue2 = std::string( XMLString::transcode( childNode2->getFirstChild()->getNodeValue() ) );

                                        newTask = new VMFileCopyTask( childNodeValue1, childNodeValue2 );
                                        if( newTask )
                                        {
                                            tasks.push_back( newTask );
                                            result = true;
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "Invalid child node for type " << typeStr << ": " << childNodeName2 << std::endl;
                                    }
                                }
                            }
                            else
                            {
                                std::cout << "Invalid child node for type " << typeStr << ": " << childNodeName1 << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Failed to find first child node for type " << typeStr << std::endl;
                        }
                    }
                    else if( "vm_run_program" == typeStr )
                    {
                        childNode1 = node->getChildNodes()->item( 1 );
                        if( childNode1 )
                        {
                            childNodeName1 = std::string( XMLString::transcode( childNode1->getNodeName() ) );
                            if( "command" == childNodeName1 )
                            {
                                childNodeValue1 = std::string( XMLString::transcode( childNode1->getFirstChild()->getNodeValue() ) );
                                newTask = new VMRunTask( childNodeValue1 );
                                if( newTask )
                                {
                                    tasks.push_back( newTask );
                                    result = true;
                                }
                            }
                            else
                            {
                                std::cout << "Invalid child node for type " << typeStr << ": " << childNodeName1 << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Failed to find first child node for type " << typeStr << std::endl;
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
    else if( "#text" == nodeName )
    {
        // Empty text node, skip it.
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

