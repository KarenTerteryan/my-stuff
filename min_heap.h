template<class T, class Less = std::less<T>>
class min_heap
{
public:
    class handle
    {
    public:
        bool valid() const { return m_index != 0; }

    private:
        size_t m_index;
    };

    min_heap(T max_value, const Less& less = Less{}) : m_less(less)
    {
        m_el.push_back(T{});
        m_id.resize(max_value + 1);
    }

    T pop() {
        T res = m_el[1];
        m_id[res] = 0;
        if (m_el.size() > 2) {
            m_el[1] = m_el[m_el.size() - 1];
            m_id[m_el[1]] = 1;
        }
        m_el.pop_back();
        sift_down(1);
        return res;
    }

    void push(const T& item) {
        m_el.push_back(item);
        m_id[item] = m_el.size() - 1;
        sift_up(m_el.size() - 1);
    }

    bool empty() const {
        return m_el.size() == 1;
    }

    void reserve(size_t capacity) {
        m_el.reserve(capacity + 1);
        m_id.reserve(capacity + 1);
    }

    size_t capacity() const {
        return m_el.capacity() - 1;
    }

    handle get_handle(const T& item) const {
        return item < m_id.size() ? handle{m_id[item]} : handle{0};
    }

    bool contains(const T& item) const {
        return item < m_id.size() && m_id[item] != 0;
    }

    void increase_prio(const T& item) {
        sift_up(m_id[item]);
    }

    void decrease_prio(const T& item) {
        sift_down(m_id[item]);
    }

    void increase_prio(const handle& h) {
        sift_up(h.m_index);
    }

    void decrease_prio(const handle& h) {
        sift_down(h.m_index);
    }

private:
    void sift_down(size_t i) {
        size_t c = i * 2;
        const size_t N = m_el.size() - 1;
        while (c <= N) {
            if (c + 1 <= N && m_less(m_el[c + 1], m_el[c]))
                c++;
            if (!m_less(m_el[c], m_el[i]))
                break;
            swap(m_id[m_el[c]], m_id[m_el[i]]);
            swap(m_el[c], m_el[i]);
            i = c;
            c *= 2;
        }
    }

    void sift_up(size_t i) {
        int p = i / 2;
        while (p >= 1 && m_less(m_el[i], m_el[p])) {
            swap(m_id[m_el[i]], m_id[m_el[p]]);
            swap(m_el[i], m_el[p]);
            i = p;
            p /= 2;
        }
    }

    Less m_less;
    vector<T> m_el;
    vector<int> m_id;
};
