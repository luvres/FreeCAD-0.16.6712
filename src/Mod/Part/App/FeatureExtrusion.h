/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#ifndef PART_FEATUREEXTRUSION_H
#define PART_FEATUREEXTRUSION_H

#include <App/PropertyStandard.h>
#include <App/PropertyUnits.h>
#include "PartFeature.h"
#include <TopoDS_Face.hxx>

namespace Part
{

class Extrusion : public Part::Feature
{
    PROPERTY_HEADER(Part::Extrusion);

public:
    Extrusion();

    App::PropertyLink Base;
    App::PropertyVector Dir;
    App::PropertyBool Solid;
    App::PropertyAngle TaperAngle;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the view provider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderExtrusion";
    }
    //@}

private:
    bool isInside(const TopoDS_Wire&, const TopoDS_Wire&) const;
    TopoDS_Face validateFace(const TopoDS_Face&) const;
    TopoDS_Shape makeFace(const std::vector<TopoDS_Wire>&) const;
    TopoDS_Shape makeFace(std::list<TopoDS_Wire>&) const; // for internal use only
    void makeDraft(double, const gp_Vec&, bool, const TopoDS_Shape&, std::list<TopoDS_Shape>&) const;

private:
    class Wire_Compare;
};

} //namespace Part


#endif // PART_FEATUREEXTRUSION_H
