/*
        qdate.cpp

        See qdate.h for documentation.

        Compile this file and link it with your code.

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc., All Rights Reserved.
This part of the software is released under ONE of the following licenses:
GPL, the gSOAP public license, OR Genivia's license for commercial use.
--------------------------------------------------------------------------------
gSOAP public license.

The contents of this file are subject to the gSOAP Public License Version 1.3
(the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at
http://www.cs.fsu.edu/~engelen/soaplicense.html
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the License.

The Initial Developer of the Original Code is Robert A. van Engelen.
Copyright (C) 2000-2016, Robert van Engelen, Genivia, Inc., All Rights Reserved.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org

This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

/* When using soapcpp2 option -q<name> or -p<name>, you need to change "soapH.h" below */

/* include soapH.h generated by soapcpp2 from .h file containing #import "qdate.h" */
#ifdef SOAP_H_FILE      /* if set, use the soapcpp2-generated fileH.h file as specified with: cc ... -DSOAP_H_FILE=fileH.h */
# include "stdsoap2.h"
# include SOAP_XSTRINGIFY(SOAP_H_FILE)
#else
# include "soapH.h"	/* or manually replace with soapcpp2-generated *H.h file */
#endif

static void * instantiate_xsd__date(struct soap*, int, const char*, const char*, size_t*);

static int delete_xsd__date(struct soap*, struct soap_clist*);

static void copy_xsd__date(struct soap*, int, int, void*, size_t, const void*, void**);

void soap_serialize_xsd__date(struct soap *soap, QDate const *a)
{
  (void)soap; (void)a; /* appease -Wall -Werror */
}

void soap_default_xsd__date(struct soap *soap, QDate *a)
{
  (void)soap; /* appease -Wall -Werror */
  *a = QDate();
}

int soap_out_xsd__date(struct soap *soap, char const *tag, int id, QDate const *a, char const *type)
{
  if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_xsd__date), type)
   || soap_string_out(soap, soap_xsd__date2s(soap, *a), 0))
    return soap->error;
  return soap_element_end_out(soap, tag);
}

QDate *soap_in_xsd__date(struct soap *soap, char const *tag, QDate *a, char const *type)
{
  if (soap_element_begin_in(soap, tag, 0, NULL))
    return NULL;
  if (*soap->type
   && soap_match_att(soap, soap->type, type)
   && soap_match_att(soap, soap->type, ":date"))
  {
    soap->error = SOAP_TYPE;
    soap_revert(soap);
    return NULL;
  }
  a = (QDate*)soap_id_enter(soap, soap->id, a, SOAP_TYPE_xsd__date, sizeof(QDate), NULL, NULL, instantiate_xsd__date, NULL);
  if (*soap->href)
  {
    a = (QDate*)soap_id_forward(soap, soap->href, a, 0, SOAP_TYPE_xsd__date, 0, sizeof(QDate), 0, copy_xsd__date, NULL);
  }
  else if (a)
  {
    if (soap_s2xsd__date(soap, soap_value(soap), a))
      return NULL;
  }
  if (soap->body && soap_element_end_in(soap, tag))
    return NULL;
  return a;
}

const char * soap_xsd__date2s(struct soap *soap, QDate a)
{
  /* YYYY-MM-DDZ */
  if (!a.isValid())
    a = QDate(1, 1, 1);
  QString str = a.toString("yyyy-MM-ddZ");
  QByteArray ba = str.toLatin1();
  soap_strcpy(soap->tmpbuf, qstrlen(ba)+1, ba.constData());
  return soap->tmpbuf;
}

int soap_s2xsd__date(struct soap *soap, const char *s, QDate *a)
{
  *a = QDate();
  if (s)
  {
    char *t;
    unsigned long d;
    int yr = 0, mon = 0, day = 0;
    d = soap_strtoul(s, &t, 10);
    if (*t == '-')
    {
      /* YYYY-MM-DD */
      yr = (int)d;
      mon = (int)soap_strtoul(t + 1, &t, 10);
      day = (int)soap_strtoul(t + 1, &t, 10);
    }
    else if (!(soap->mode & SOAP_XML_STRICT))
    {
      /* YYYYMMDD */
      yr = (int)(d / 10000);
      mon = (int)(d / 100 % 100);
      day = (int)(d % 100);
    }
    else
    {
      return soap->error = SOAP_TYPE;
    }
    //set the date
    a->setDate(yr, mon, day);
    //grab the timezone to check validity
    if (*t == ' ' && !(soap->mode & SOAP_XML_STRICT))
      t++;
    if (*t)
    {
#ifndef WITH_NOZONE
      if (*t == '+' || *t == '-')
      {
        soap_strtol(t, &t, 10);
        if (*t == ':')
          soap_strtol(t + 1, &t, 10);
        if (*t)
          return soap->error = SOAP_TYPE;
      }
      else if (*t != 'Z')
      {
        return soap->error = SOAP_TYPE;
      }
#endif
    }
    else
    {
      /* no UTC or timezone, so assume we got a localtime */
    }
  }
  return soap->error;
}

static void * instantiate_xsd__date(struct soap *soap, int n, const char *type, const char *arrayType, size_t *size)
{
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "soap_instantiate_xsd__date(%d, %s, %s)\n", n, type?type:"", arrayType?arrayType:""));
  struct soap_clist *cp = soap_link(soap, SOAP_TYPE_xsd__date, n, delete_xsd__date);
  (void)type; (void)arrayType; /* appease -Wall -Werror */
  if (!cp)
    return NULL;
  if (n < 0)
  {	cp->ptr = SOAP_NEW(soap, QDate);
    if (size)
      *size = sizeof(QDate);
  }
  else
  {	cp->ptr = SOAP_NEW_ARRAY(soap, QDate, n);
    if (size)
      *size = n * sizeof(QDate);
  }
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Instantiated location=%p\n", cp->ptr));
  if (!cp->ptr)
    soap->error = SOAP_EOM;
  return (QDate*)cp->ptr;
}

static int delete_xsd__date(struct soap *soap, struct soap_clist *p)
{
  (void)soap; /* appease -Wall -Werror */
  if (p->type == SOAP_TYPE_xsd__date)
  {
    if (p->size < 0)
      SOAP_DELETE(soap, static_cast<QDate*>(p->ptr), QDate);
    else
      SOAP_DELETE_ARRAY(soap, static_cast<QDate*>(p->ptr), QDate);
    return SOAP_OK;
  }
  return SOAP_ERR;
}

static void copy_xsd__date(struct soap *soap, int st, int tt, void *p, size_t index, const void *q, void **x)
{
  (void)soap; (void)st; (void)tt; (void)index; (void)x; /* appease -Wall -Werror */
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Copying QDate %p -> %p\n", q, p));
  *(QDate*)p = *(QDate*)q;
}