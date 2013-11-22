
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import lpg.runtime.*;

public abstract class AbstractAstList extends Ast implements IAbstractArrayList<Ast>
{
    private boolean leftRecursive;
    private java.util.ArrayList list;
    public int size() { return list.size(); }
    public java.util.List getList() { return list; }
    public Ast getElementAt(int i) { return (Ast) list.get(leftRecursive ? i : list.size() - 1 - i); }
    public java.util.ArrayList getArrayList()
    {
        if (! leftRecursive) // reverse the list 
        {
            for (int i = 0, n = list.size() - 1; i < n; i++, n--)
            {
                Object ith = list.get(i),
                       nth = list.get(n);
                list.set(i, nth);
                list.set(n, ith);
            }
            leftRecursive = true;
        }
        return list;
    }
    /**
     * @deprecated replaced by {@link #addElement()}
     *
     */
    public void add(Ast element)
    {
        addElement(element);
    }

    public void addElement(Ast element)
    {
        list.add(element);
        if (leftRecursive)
             rightIToken = element.getRightIToken();
        else leftIToken = element.getLeftIToken();
    }

    public AbstractAstList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken);
        this.leftRecursive = leftRecursive;
        list = new java.util.ArrayList();
    }

    public AbstractAstList(Ast element, boolean leftRecursive)
    {
        this(element.getLeftIToken(), element.getRightIToken(), leftRecursive);
        list.add(element);
    }

    private class Itr implements java.util.Iterator<Ast> {
        java.util.Iterator<Ast> itr = list.iterator();
        public boolean hasNext() {
            return itr.hasNext();
        }
        public Ast next() {
            return itr.next();
        }
        public void remove() {
            throw new UnsupportedOperationException();
         }
    }

    private class ListItr extends Itr implements java.util.ListIterator<Ast> {
        java.util.ListIterator<Ast> list_itr;
        ListItr(int index) {
            list_itr = list.listIterator(index);
        }
        public boolean hasPrevious() {
            return list_itr.hasPrevious();
        }
        public Ast previous() {
            return list_itr.previous();
        }
        public int nextIndex() {
            return list_itr.nextIndex();
        }

        public int previousIndex() {
            return list_itr.previousIndex();
        }
        public void set(Ast o) {
            throw new UnsupportedOperationException();
        }
        public void add(Ast o) {
            throw new UnsupportedOperationException();
        }
    }
    public boolean isEmpty() {
        return list.isEmpty();
    }
    public boolean contains(Object o) {
        return list.contains(o);
    }
    public java.util.Iterator<Ast> iterator() {
        return new Itr();
    }
    public Object[] toArray() {
        return getArrayList().toArray();
    }
    public <T> T[] toArray(T[] a) {
        return (T[]) getArrayList().toArray(a);
    }
    public boolean remove(Object o) {
        throw new UnsupportedOperationException();
    }
    public boolean containsAll(java.util.Collection<?> c) {
        return list.containsAll(c);
    }
    public boolean addAll(java.util.Collection<? extends Ast> c) {
        throw new UnsupportedOperationException();
    }
    public boolean addAll(int index, java.util.Collection<? extends Ast> c) {
        throw new UnsupportedOperationException();
    }
    public boolean removeAll(java.util.Collection<?> c) {
        throw new UnsupportedOperationException();
    }
    public boolean retainAll(java.util.Collection<?> c) {
        throw new UnsupportedOperationException();
    }
    public void clear() {
        throw new UnsupportedOperationException();
    }
    public Ast get(int index) {
        return getElementAt(index);
    }
    public Ast set(int index, Ast element) {
        throw new UnsupportedOperationException();
    }
    public void add(int index, Ast element) {
        throw new UnsupportedOperationException();
    }
    public Ast remove(int index) {
        throw new UnsupportedOperationException();
    }
    public int indexOf(Object o) {
        return getArrayList().indexOf(o);
    }
    public int lastIndexOf(Object o) {
        return getArrayList().lastIndexOf(o);
    }
    public java.util.ListIterator<Ast> listIterator() {
        return new ListItr(0);
    }
    public java.util.ListIterator<Ast> listIterator(int index) {
        return new ListItr(index);
    }
    public java.util.List<Ast> subList(int fromIndex, int toIndex) {
        return getArrayList().subList(fromIndex, toIndex);
    }
}


