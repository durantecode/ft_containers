/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:41:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/03 23:02:56 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>

namespace ft
{
			/*************************************************/
			/*              ITERATOR_TRAITS                  */
			/*************************************************/
    
	template <class T>
    struct iterator_traits
	{
        typedef typename T::value_type            	value_type;
        typedef typename T::difference_type       	difference_type;
        typedef typename T::iterator_category     	iterator_category;
        typedef typename T::pointer               	pointer;
        typedef typename T::reference            	reference;
    };

    template <class T>
    struct iterator_traits<T*>
	{
        typedef T									value_type;
        typedef ptrdiff_t                  			difference_type;
        typedef std::random_access_iterator_tag		iterator_category;
        typedef T*									pointer;
        typedef T&									reference;
    };
    
	template <class T>
    struct iterator_traits<const T*>
	{
        typedef T									value_type;
        typedef ptrdiff_t                  			difference_type;
        typedef std::random_access_iterator_tag		iterator_category;
        typedef const T*							pointer;
        typedef const T&								reference;
    };

			/*************************************************/
			/*                 VECTOR_ITERATOR               */
			/*************************************************/
	
	template <class T>
	class VectorIterator
	{
		public:
			typedef T									value_type;
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T*									pointer;
			typedef const T*							const_pointer;
			typedef T&									reference;
			typedef const T&							const_reference;

		protected:
			pointer m_ptr;
		
		public:
			VectorIterator() : m_ptr(nullptr) {}
			VectorIterator(pointer ptr) : m_ptr(ptr) {}
			VectorIterator(VectorIterator const &toCopy) : m_ptr(toCopy.m_ptr) {}
			~VectorIterator() {}
			VectorIterator &operator = (VectorIterator const &toCopy)
			{
				this->m_ptr = toCopy.m_ptr;
				return (*this);
			}

			VectorIterator& operator ++ ()
			{
				this->m_ptr++;
				return (*this);
			}
			VectorIterator operator ++ (int)
			{
				VectorIterator it(*this);
				++(*this);
				return it;
			}
			VectorIterator &operator += (difference_type val)
			{
				this->m_ptr += val;
				return (*this);
			}
			VectorIterator operator + (difference_type val) const
			{
				VectorIterator it(*this);
				return (it += val);
			}
			VectorIterator& operator -- ()
			{
				this->m_ptr--;
				return *this;
			}
			VectorIterator operator -- (int)
			{
				VectorIterator it(*this);
				--(*this);
				return it;
			}
			VectorIterator &operator -= (difference_type val)
			{
				this->m_ptr -= val;
				return (*this);
			}
			VectorIterator operator - (difference_type val) const
			{
				VectorIterator it(*this);
				return (it -= val);
			}
			difference_type operator - (VectorIterator const &other) const { return (this->m_ptr - other.m_ptr); }

			reference operator * () { return (*this->m_ptr); }
			const_reference operator * () const { return (*this->m_ptr); }
			pointer operator -> () { return (this->m_ptr); }
			const_pointer operator -> () const { return (this->m_ptr); }
			reference operator [] (difference_type val) { return (*(this->m_ptr + val)); }
			const_reference operator [] (difference_type val) const { return (*(this->m_ptr + val)); }
			bool operator == (const VectorIterator &it) const { return (this->m_ptr == it.m_ptr); }
			bool operator != (const VectorIterator &it) const { return (this->m_ptr != it.m_ptr); }
			bool operator > (const VectorIterator &it) const { return (this->m_ptr > it.m_ptr); }
			bool operator >= (const VectorIterator &it) const { return (this->m_ptr >= it.m_ptr); }
			bool operator < (const VectorIterator &it) const { return (this->m_ptr < it.m_ptr); }
			bool operator <= (const VectorIterator &it) const { return (this->m_ptr <= it.m_ptr); }

	};


			/*************************************************/
			/*            REVERSE_VECTOR_ITERATOR            */
			/*************************************************/

	template <class T>
	class ReverseVectorIterator
	{
		public:
			typedef T												iterator_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;

		private:
			iterator_type m_iter;

		public:
			ReverseVectorIterator()	: m_iter() {}
			ReverseVectorIterator(iterator_type it)	: m_iter(it) {}
			~ReverseVectorIterator() {}
			
			template <class Iter>
			ReverseVectorIterator(const ReverseVectorIterator<Iter> &toCopy) : m_iter(toCopy.base()) {}

			template <class Iter>
			ReverseVectorIterator& operator = (const ReverseVectorIterator<Iter> &other) { m_iter = other.base(); return *this; }

			iterator_type base() const { return this->m_iter; }

			ReverseVectorIterator operator + (difference_type n) const { return ReverseVectorIterator(this->m_iter - n); }
			ReverseVectorIterator& operator ++ () { --this->m_iter; return *this; }
			ReverseVectorIterator operator ++ (int)
			{
				ReverseVectorIterator tmp = *this;
				--this->m_iter;
				return tmp;
			}
			ReverseVectorIterator& operator += (difference_type n)	{ this->m_iter -= n; return *this; }
			ReverseVectorIterator operator - (difference_type n) const { return ReverseVectorIterator(this->m_iter + n); }
			ReverseVectorIterator& operator -- () { ++this->m_iter; return *this; }
			ReverseVectorIterator operator -- (int)
			{
				ReverseVectorIterator tmp = *this;
				++this->m_iter;
				return  tmp;
			}
			ReverseVectorIterator operator -= (difference_type n) { this->m_iter += n; return *this; }

			reference operator*() const
			{
				iterator_type tmp = this->m_iter;
				return *(--tmp);
			}
			pointer operator->() const { return &(operator*()); }
			reference operator[] (difference_type n) const { return base()[-n - 1]; }
	};

	
	/*************************************************/
	/*        NON-MEMBER FUNCTIONS OVERLOADS         */
	/*************************************************/

	template <class Iter1, class Iter2>
	bool operator == (const ReverseVectorIterator<Iter1>& l, const ReverseVectorIterator<Iter2>& r) { return l.base() == r.base(); }
	template <class Iter1, class Iter2>
	bool operator != (const ReverseVectorIterator<Iter1>& l, const ReverseVectorIterator<Iter2>& r) { return l.base() != r.base(); }
	template <class Iter1, class Iter2>
	bool operator > (const ReverseVectorIterator<Iter1>& l,	const ReverseVectorIterator<Iter2>& r) { return l.base() > r.base(); }
	template <class Iter1, class Iter2>
	bool operator >= (const ReverseVectorIterator<Iter1>& l, const ReverseVectorIterator<Iter2>& r) { return l.base() >= r.base(); }
	template <class Iter1, class Iter2>
	bool operator < (const ReverseVectorIterator<Iter1>& l,	const ReverseVectorIterator<Iter2>& r) { return l.base() < r.base(); }
	template <class Iter1, class Iter2>
	bool operator <= (const ReverseVectorIterator<Iter1>& l, const ReverseVectorIterator<Iter2>& r) { return l.base() <= r.base(); }

	template <class Iter>
	ReverseVectorIterator<Iter>	operator + (typename ReverseVectorIterator<Iter>::difference_type n, const ReverseVectorIterator<Iter> &rev_iter) { return rev_iter + n; }

	template <class Iter>
	typename ReverseVectorIterator<Iter>::difference_type operator - (const ReverseVectorIterator<Iter> &l, const ReverseVectorIterator<Iter> &r) { return r.base() - l.base(); }

}
