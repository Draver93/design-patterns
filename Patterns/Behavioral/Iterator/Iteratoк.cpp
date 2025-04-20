#include "Iterator.h"

#include <queue>
#include <stack>


namespace iterator_pattern {

	class Collection {
	public:
		virtual void add(int val) = 0;
	};

	class BinaryTree : public Collection {
	private:
		friend class BFSBinaryTreeIterator;
		friend class DFSBinaryTreeIterator;

	private:
		struct Node {
			int value;
			std::shared_ptr<Node> left, right;
			Node(int val) : value(val) {}
		};
		std::shared_ptr<Node> m_root;

		void add_recursive(int val, std::shared_ptr<Node> curr) {
			if (curr->value == val) return; //Do not allow dups

			if (val > curr->value) {
				if (curr->right) add_recursive(val, curr->right);
				else curr->right = std::make_shared<Node>(val);
			}
			else {
				if (curr->left) add_recursive(val, curr->left);
				else curr->left = std::make_shared<Node>(val);
			}
		}

	public:
		void add(int val) {
			if (!m_root) m_root = std::make_shared<Node>(val);
			else {
				add_recursive(val, m_root);
			}
		};
	};


	class Iterator {
	protected:
		int m_value = 0;

	public:
		virtual bool has_next() = 0;
		virtual int next() = 0;

	};

	class DFSBinaryTreeIterator : public Iterator {
	private:
		std::shared_ptr<BinaryTree> m_binary_tree;
		std::stack<std::shared_ptr<BinaryTree::Node>> m_traversed;

	public:
		DFSBinaryTreeIterator(std::shared_ptr<BinaryTree> collection) : m_binary_tree(collection) {
			if (m_binary_tree->m_root) {
				m_traversed.push(m_binary_tree->m_root);
			}
		}

		bool has_next() { return !m_traversed.empty(); }

		int next() {
			if (!has_next()) throw std::out_of_range("No more elements");

			std::shared_ptr<BinaryTree::Node> next = m_traversed.top();
			m_traversed.pop();

			if (next->right) m_traversed.push(next->right);
			if (next->left) m_traversed.push(next->left);

			m_value = next->value;
			return m_value;
		}
	};

	class BFSBinaryTreeIterator : public Iterator {
	private:
		std::shared_ptr<BinaryTree> m_binary_tree;
		std::queue<std::shared_ptr<BinaryTree::Node>> m_traversed;

	public:
		BFSBinaryTreeIterator(std::shared_ptr<BinaryTree> collection) : m_binary_tree(collection) {
			if (m_binary_tree->m_root) {
				m_traversed.push(m_binary_tree->m_root);
			}
		}

		bool has_next() { return !m_traversed.empty(); }

		int next() {
			if (!has_next()) throw std::out_of_range("No more elements");

			std::shared_ptr<BinaryTree::Node> next = m_traversed.front();
			m_traversed.pop();

			if (next->left) m_traversed.push(next->left);
			if (next->right) m_traversed.push(next->right);

			m_value = next->value;
			return m_value;
		}
	};
}


std::string IteratorPattern::get_info() {
	return "Name: Iterator Pattern.\nType: Behavioral.\nDescription: The Iterator pattern provides a way to traverse a collection while hiding its underlying implementation details.";
}

int IteratorPattern::run() {

	using namespace iterator_pattern;

	std::shared_ptr<BinaryTree> binary_tree = std::make_shared<BinaryTree>();
	binary_tree->add(10);
	binary_tree->add(2);
	binary_tree->add(14);
	binary_tree->add(3);
	binary_tree->add(7);
	binary_tree->add(16);

	std::cout << "\n" << "Iterator based on BFS traverse:" << std::endl;
	std::shared_ptr<Iterator> bfs_it = std::make_shared<BFSBinaryTreeIterator>(binary_tree);
	while (true) {
		if (bfs_it->has_next()) std::cout << bfs_it->next() << " ";
		else break;
	}

	std::cout << "\n" << "Iterator based on DFS traverse:" << std::endl;
	std::shared_ptr<Iterator> dfs_it = std::make_shared<DFSBinaryTreeIterator>(binary_tree);
	while (true) {
		if (dfs_it->has_next()) std::cout << dfs_it->next() << " ";
		else break;
	}

	std::cout << std::endl;

	return 0;
}