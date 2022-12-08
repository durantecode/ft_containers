/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:41:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/08 23:49:42 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
			/*************************************************/
			/*                 VECTOR_ITERATOR               */
			/*************************************************/
	
	template <class T, class Pointer, class Reference>
	class VectorIterator
	{
		public:
			typedef T					value_type;
			typedef std::ptrdiff_t		difference_type;
			typedef Pointer				pointer;
			typedef Reference			reference;

			typedef VectorIterator<T, Pointer, Reference>	iter_type;
			typedef VectorIterator<T, T*, T&>				iterator;
			typedef std::random_access_iterator_tag			iterator_category;

		private:
			pointer m_ptr;
		
		public:
			VectorIterator() : m_ptr(NULL) {}
			VectorIterator(const pointer ptr) : m_ptr(ptr) {}
			VectorIterator(iterator const &toCopy) : m_ptr((toCopy.getBase())) {}
			~VectorIterator() {}

			pointer getBase() const { return this->m_ptr; }
			iter_type &operator = (iter_type const &toCopy)
			{
				this->m_ptr = toCopy.m_ptr;
				return (*this);
			}

			iter_type& operator ++ ()
			{
				this->m_ptr++;
				return (*this);
			}
			iter_type operator ++ (int)
			{
				iter_type it(*this);
				++(*this);
				return it;
			}
			iter_type &operator += (difference_type val)
			{
				this->m_ptr += val;
				return (*this);
			}
			iter_type operator + (difference_type val) const
			{
				iter_type it(*this);
				return (it += val);
			}
			iter_type& operator -- ()
			{
				this->m_ptr--;
				return *this;
			}
			iter_type operator -- (int)
			{
				iter_type it(*this);
				--(*this);
				return it;
			}
			iter_type &operator -= (difference_type val)
			{
				this->m_ptr -= val;
				return (*this);
			}
			iter_type operator - (difference_type val) const
			{
				iter_type it(*this);
				return (it -= val);
			}
			difference_type operator - (iter_type const &other) const { return (this->m_ptr - other.m_ptr); }

			reference operator * () { return (*this->m_ptr); }
			pointer operator -> () { return (this->m_ptr); }
			reference operator [] (difference_type val) { return (*(this->m_ptr + val)); }
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

			reference operator*()
			{
				iterator_type tmp = this->m_iter;
				return *(--tmp);
			}
			pointer operator->() { return &(operator*()); }
			reference operator[] (difference_type n) { return base()[-n - 1]; }

			friend bool operator == (const ReverseVectorIterator &l, const ReverseVectorIterator &r) { return l.base() == r.base(); }
			friend bool operator != (const ReverseVectorIterator &l, const ReverseVectorIterator &r) { return l.base() != r.base(); }
			friend bool operator >  (const ReverseVectorIterator &l, const ReverseVectorIterator &r) { return l.base() >  r.base(); }
			friend bool operator >= (const ReverseVectorIterator &l, const ReverseVectorIterator &r) { return l.base() >= r.base(); }
			friend bool operator <  (const ReverseVectorIterator &l, const ReverseVectorIterator &r) { return l.base() <  r.base(); }
			friend bool operator <= (const ReverseVectorIterator &l, const ReverseVectorIterator &r) { return l.base() <= r.base(); }

			friend ReverseVectorIterator operator + (typename ReverseVectorIterator::difference_type n, const ReverseVectorIterator &rev_iter) { return rev_iter + n; }
			friend typename ReverseVectorIterator::difference_type operator - (const ReverseVectorIterator &l, const ReverseVectorIterator &r) { return r.base() - l.base(); }
	};
}
