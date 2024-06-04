Rails.application.routes.draw do
  resources :passangers
  root 'home#index'
end
