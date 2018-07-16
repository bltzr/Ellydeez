//
//  DMXLine.hpp
//  Ellydee
//
//  Created by Pascal Baltazar on 22/05/2018.
//

#ifndef DMXLine_hpp
#define DMXLine_hpp

#include "LineBase.hpp"

namespace Sinks {


class DMXLine : public LineBase {
    
public:
    void send();
    
};

} // namespace Sinks

#endif /* DMXLine_hpp */
