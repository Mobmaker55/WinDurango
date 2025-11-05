#include "pch.h"
#include "Windows.Xbox.ApplicationModel.Store.Product.h"
#include "Windows.Xbox.ApplicationModel.Store.Product.g.cpp"
#include "Windows.Xbox.ApplicationModel.Store.ProductPurchasedEventArgs.h"

namespace winrt::Windows::Xbox::ApplicationModel::Store::implementation
{
    winrt::Windows::Foundation::IAsyncAction Product::ShowPurchaseAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring offer)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowDetailsAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring productId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowMarketplaceAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Xbox::ApplicationModel::Store::ProductItemTypes inputProductItemType, hstring inputProductId, winrt::Windows::Xbox::ApplicationModel::Store::ProductItemTypes resultProductItemTypes)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowRedeemCodeAsync(winrt::Windows::Xbox::System::IUser user, hstring offer)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowSubscriptionAsync(winrt::Windows::Xbox::System::IUser user, hstring productId, uint32_t privilegeId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::ApplicationModel::Store::PrivilegeCheckResult> Product::CheckPrivilegeAsync(winrt::Windows::Xbox::System::IUser user, uint32_t privilegeId, bool attemptResolution, hstring friendlyDisplay)
    {
        auto args = winrt::make<implementation::ProductPurchasedEventArgs>();
        co_return PrivilegeCheckResult::NoIssue;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::ApplicationModel::Store::PrivilegeCheckResult> Product::CheckPrivilegesAsync(winrt::Windows::Xbox::System::IUser user, winrt::Windows::Foundation::Collections::IVectorView<uint32_t> privilegeIds, bool attemptResolution, hstring friendlyDisplay)
    {
        auto args = winrt::make<implementation::ProductPurchasedEventArgs>();
        co_return PrivilegeCheckResult::NoIssue;
    }
    winrt::event_token Product::ProductPurchased(winrt::Windows::Xbox::ApplicationModel::Store::ProductPurchasedEventHandler const& handler)
    {
        return m_productPurchasedEvent.add(handler);
    }
    void Product::ProductPurchased(winrt::event_token const& token) noexcept
    {
        m_productPurchasedEvent.remove(token);
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowPurchaseForStoreIdAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring storeId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowDetailsForStoreIdAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring storeId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowUpsellAsync(winrt::Windows::Xbox::System::IUser requestingUser, uint32_t privilegeId, hstring prioritizedSku, uint32_t upsellEntryPoint, hstring referProductId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction Product::ShowUpsellThirdPartyNoticeAsync(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
