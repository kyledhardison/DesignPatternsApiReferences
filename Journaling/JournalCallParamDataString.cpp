#include "JournalCallParamDataString.h"
#include "JournalingInternal.h"
#include "JournalFile.h"

using namespace Journal;

JournalCallParamDataString::JournalCallParamDataString(std::string paramName,
    ParameterMetaType paramType, std::string value) :
    JournalCallParamData(paramName, paramType,
        JournalCallParamData::ParameterBasicType::STRING), m_value(value)
{

}

void JournalCallParamDataString::Journal()
{
    if (this->m_paramType == JournalCallParamData::ParameterMetaType::INPUT)
    {
        //There is a bug here, all \ in the string need to be replaced with \\
        // i.e. if d:\dir\some.prt  we need to actualy change this to 
        //         d:\\dir\\some.prt
        
        size_t start_pos = 0;
        std::string findString = "\\";
        std::string replaceString = "\\\\";
        while ((start_pos = m_value.find(findString, start_pos)) != std::string::npos) {
            m_value.replace(start_pos, findString.length(), replaceString);
            start_pos += replaceString.length();
        }

        std::string jnlString = "\"" + m_value + "\"";
        GetActiveJournalFile()->WriteToFile(jnlString);
    }
    else if (this->m_paramType == JournalCallParamData::ParameterMetaType::OUTPUT)
    {
        throw std::exception("NIY ");
    }
    else // RETURN
    {
        throw std::exception("NIY");
    }


}