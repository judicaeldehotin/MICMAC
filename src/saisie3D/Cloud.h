﻿#ifndef __CLOUD__
#define __CLOUD__

#include <vector>
#include <string>

#include "StdAfx.h"

#ifdef Int
    #undef Int
#endif
#include <QColor>

namespace Cloud_
{
    class Vertex
    {
        public:
            Vertex();
            Vertex(Pt3dr, QColor);

            float x() {return m_position.x;}
            float y() {return m_position.y;}
            float z() {return m_position.z;}

            Pt3dr   getCoord()   {return m_position;}
            QColor  getColor()   {return m_color;}

            //! States if a point is visible (ie: selected)
            bool    isVisible()  {return m_bVisible;}

            void setCoord(Pt3dr const &aPt)     {m_position = aPt;}
            void setColor(QColor const &aCol)   {m_color = aCol;}
            void setVisible(bool aVis)          {m_bVisible = aVis;}

        private:
            Pt3dr   m_position;
            QColor  m_color;
            bool    m_bVisible;

    };

    class Cloud
    {
        public:
            Cloud();
            Cloud(std::vector<Vertex> const &);

            static Cloud* loadPly(std::string,  void (*incre)(int, void *) = NULL, void *obj = NULL);

            void    addVertex( const Vertex & );
            Vertex& getVertex( unsigned int );
            int     size();

            void    setTranslation( const Pt3dr & aPt ) {m_translation = aPt;}
            Pt3dr   getTranslation(){return m_translation;}

            void    setScale( const float & aS ) {m_scale = aS;}
            float   getScale(){return m_scale;}

            void    clear();

        private:
            std::vector<Vertex> m_vertices;
            Pt3dr m_translation;
            float m_scale;
    };

}

#endif
