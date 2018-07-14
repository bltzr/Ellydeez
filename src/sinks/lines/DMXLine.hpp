//
//  DMXLine.hpp
//  Ellydee
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef DMXLine_hpp
#define DMXLine_hpp

#include "outLine.hpp"

namespace Sinks {


class DMXLine : public OutLine
{
public:
    void sendLine();
    
};

} // namespace Sinks

#endif /* DMXLine_hpp */
