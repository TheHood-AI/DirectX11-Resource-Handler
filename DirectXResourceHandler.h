#pragma once
#include <memory>
#include <d3d11.h>

// Uses a std::unique_ptr to manage a DirectX resource
// Once this object goes out of scope, it calls Release() on the DirectX resource
template<typename TDirectXResource>
class TDirectXResourceHandler
{
private:
	using DeleteFunc = decltype([](TDirectXResource* aOwnedResource) {aOwnedResource->Release(); });
	using TResourcePtr = std::unique_ptr<TDirectXResource, DeleteFunc>;
public:

	TDirectXResourceHandler() = default;
	TDirectXResourceHandler(TDirectXResource* aResource);
	
	// Returns true if resource is not nullptr
	[[nodiscard]] inline bool IsValid() const;

	// Returns the raw resource pointer
	TDirectXResource* Get();
	TDirectXResource* Get()const;
	// Returns the raw resource pointer
	TDirectXResource* operator*();
	TDirectXResource* operator*()const;
private:
	TResourcePtr myResource;
};

template<typename TDirectXResource>
inline TDirectXResourceHandler<TDirectXResource>::TDirectXResourceHandler(TDirectXResource* aResource)
{
	if (aResource)
		myResource = TResourcePtr(aResource);
}

template<typename TDirectXResource>
inline bool TDirectXResourceHandler<TDirectXResource>::IsValid()const
{
	return myResource.get();
}

template<typename TDirectXResource>
inline TDirectXResource* TDirectXResourceHandler<TDirectXResource>::Get()
{
	return *(*this);
}

template<typename TDirectXResource>
inline TDirectXResource* TDirectXResourceHandler<TDirectXResource>::Get() const
{
	return *(*this);
}

template<typename TDirectXResource>
inline TDirectXResource* TDirectXResourceHandler<TDirectXResource>::operator*()
{
	return static_cast<const TDirectXResourceHandler<TDirectXResource>*>(this)->operator*();
}

template<typename TDirectXResource>
inline TDirectXResource* TDirectXResourceHandler<TDirectXResource>::operator*() const
{
	return myResource.get();
}
