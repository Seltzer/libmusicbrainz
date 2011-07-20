/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/Work.h"

#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Alias.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"

class MusicBrainz4::CWorkPrivate
{
	public:
		CWorkPrivate()
		:	m_ArtistCredit(0),
			m_AliasList(0),
			m_RelationList(0),
			m_TagList(0),
			m_UserTagList(0),
			m_Rating(0),
			m_UserRating(0)
		{
		}

		std::string m_ID;
		std::string m_Type;
		std::string m_Title;
		CArtistCredit *m_ArtistCredit;
		std::string m_ISWC;
		std::string m_Disambiguation;
		CGenericList<CAlias> *m_AliasList;
		CGenericList<CRelation> *m_RelationList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz4::CWork::CWork(const XMLNode& Node)
:	CEntity(),
	m_d(new CWorkPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Work node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CWork::CWork(const CWork& Other)
:	CEntity(),
	m_d(new CWorkPrivate)
{
	*this=Other;
}

MusicBrainz4::CWork& MusicBrainz4::CWork::operator =(const CWork& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Title=Other.m_d->m_Title;

		if (Other.m_d->m_ArtistCredit)
			m_d->m_ArtistCredit=new CArtistCredit(*Other.m_d->m_ArtistCredit);

		m_d->m_ISWC=Other.m_d->m_ISWC;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;

		if (Other.m_d->m_AliasList)
			m_d->m_AliasList=new CGenericList<CAlias>(*Other.m_d->m_AliasList);

		if (Other.m_d->m_RelationList)
			m_d->m_RelationList=new CGenericList<CRelation>(*Other.m_d->m_RelationList);

		if (Other.m_d->m_TagList)
			m_d->m_TagList=new CGenericList<CTag>(*Other.m_d->m_TagList);

		if (Other.m_d->m_UserTagList)
			m_d->m_UserTagList=new CGenericList<CUserTag>(*Other.m_d->m_UserTagList);

		if (Other.m_d->m_Rating)
			m_d->m_Rating=new CRating(*Other.m_d->m_Rating);

		if (Other.m_d->m_UserRating)
			m_d->m_UserRating=new CUserRating(*Other.m_d->m_UserRating);
	}

	return *this;
}

MusicBrainz4::CWork::~CWork()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CWork::Cleanup()
{
	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;

	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

	delete m_d->m_RelationList;
	m_d->m_RelationList=0;

	delete m_d->m_TagList;
	m_d->m_TagList=0;

	delete m_d->m_UserTagList;
	m_d->m_UserTagList=0;

	delete m_d->m_Rating;
	m_d->m_Rating=0;

	delete m_d->m_UserRating;
	m_d->m_UserRating=0;
}

bool MusicBrainz4::CWork::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else if ("type"==Name)
		m_d->m_Type=Value;
	else
	{
		std::cerr << "Unrecognised work attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CWork::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("artist-credit"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ArtistCredit);
	}
	else if ("iswc"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ISWC);
	}
	else if ("disambiguation"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("alias-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_AliasList);
	}
	else if ("relation-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_RelationList);
	}
	else if ("tag-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_TagList);
	}
	else if ("user-tag-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_UserTagList);
	}
	else if ("rating"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Rating);
	}
	else if ("user-rating"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_UserRating);
	}
	else
	{
		std::cerr << "Unrecognised work element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CWork::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CWork::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CWork::Title() const
{
	return m_d->m_Title;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CWork::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

std::string MusicBrainz4::CWork::ISWC() const
{
	return m_d->m_ISWC;
}

std::string MusicBrainz4::CWork::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz4::CGenericList<MusicBrainz4::CAlias> *MusicBrainz4::CWork::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelation> *MusicBrainz4::CWork::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTag> *MusicBrainz4::CWork::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CUserTag> *MusicBrainz4::CWork::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CWork::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CWork::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CWork& Work)
{
	os << "Work:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&Work;

	os << *Base << std::endl;

	os << "\tID:             " << Work.ID() << std::endl;
	os << "\tWork:           " << Work.Type() << std::endl;
	os << "\tTitle:          " << Work.Title() << std::endl;
	if (Work.ArtistCredit())
		os << Work.ArtistCredit() << std::endl;
	os << "\tISWC:           " << Work.ISWC() << std::endl;

	os << "\tDisambiguation: " << Work.Disambiguation() << std::endl;
	if (Work.AliasList())
		os << Work.AliasList() << std::endl;

	if (Work.RelationList())
		os << Work.RelationList() << std::endl;

	if (Work.TagList())
		os << Work.TagList() << std::endl;

	if (Work.UserTagList())
		os << Work.UserTagList() << std::endl;

	if (Work.Rating())
		os << Work.Rating() << std::endl;

	if (Work.UserRating())
		os << Work.UserRating() << std::endl;

	return os;
}

