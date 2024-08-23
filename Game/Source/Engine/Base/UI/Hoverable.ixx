export module fbc.Hoverable;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import std;

namespace fbc {
	export class Hoverable : public FWindow::Element {
	public:
		class Token {
		public:
			~Token() {
				if (source) {
					if (source->tokens) {
						std::erase(*source->tokens, this);
					}
					source = nullptr;
				}
			}
			Token(Token&& other) noexcept {
				if (other.source) {
					this->source = other.source;
					if (other.source->tokens) {
						std::ranges::replace(other.source->tokens->begin(), other.source->tokens->end(), &other, this);
					}
					other.source = nullptr;
				}
			}

			Hoverable* operator ->() const { return source; }
			operator bool() const { return source != nullptr; }
			operator Hoverable* () const { return source; }
			operator Hoverable& () const { return *source; }
		private:
			Token(Hoverable* source): source(source) {}

			Hoverable* source;
			friend Hoverable;
		};

		Hoverable(FWindow& window) : Element(window) {}
		Hoverable(Hoverable&& other) noexcept : Element(other.win) {
			if (other.tokens) {
				tokens = move(other.tokens);
				for (Token* token : *tokens) {
					token->source = this;
				}
			}
		}
		virtual ~Hoverable() override {
			if (tokens) {
				for (Token* token : *tokens) {
					token->source = nullptr;
				}
			}
		};

		inline virtual bool isHovered() { return getHb()->isHovered(); }
		inline virtual float getBeginX() { return getHb()->x; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getBeginY() { return getHb()->y; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getEndX() { return getHb()->x + getHb()->w; } // The right-most end X coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual float getEndY() { return getHb()->y + getHb()->h; } // The bottom-most end Y coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual Hoverable& setHbExactPos(const float x, const float y) { return getHb()->setRealPos(x, y), * this; }
		inline virtual Hoverable& setHbExactPosX(const float x) { return getHb()->setRealPosX(x), * this; }
		inline virtual Hoverable& setHbExactPosY(const float y) { return getHb()->setRealPosY(y), * this; }
		inline virtual Hoverable& setHbOffsetPos(const float x, const float y) { return getHb()->setOffPos(x, y), * this; }
		inline virtual Hoverable& setHbOffsetPosX(const float x) { return getHb()->setOffPosX(x), * this; }
		inline virtual Hoverable& setHbOffsetPosY(const float y) { return getHb()->setOffPosY(y), * this; }

		Token makeToken();

		virtual Hitbox* getHb() = 0;
	private:
		uptr<vec<Token*>> tokens;
	};

	Hoverable::Token Hoverable::makeToken() {
		Token newToken = Token(this);
		if (!tokens) {
			tokens = make_unique<vec<Token*>>();
		}
		tokens->push_back(&newToken);
		return newToken;
	}
}